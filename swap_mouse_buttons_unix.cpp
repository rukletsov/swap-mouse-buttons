
#include <iostream>
#include <utility>
#include <cstdlib>
#include <X11/Xlib.h>
#include <boost/scope_exit.hpp>

// According to the xmodmap, there are eight bits of buttons.
#define MAX_BUTTON_CODES 256

int main()
{
    // Define a delayed release of the display pointer.
    Display* display;
    BOOST_SCOPE_EXIT( (&display) )
    {
        if(display)
        {
            XCloseDisplay (display);
            display = NULL;
        }
    } BOOST_SCOPE_EXIT_END

    // Get default display.
    display = XOpenDisplay(NULL);
    if (!display)
    {
        std::cerr << "Cannot open default display." << std::endl;
        return 1;
    }

    // Get current pointer mapping.
    unsigned char pointer_map[MAX_BUTTON_CODES];
    int buttons_count = XGetPointerMapping(display, pointer_map, MAX_BUTTON_CODES);

    // We need at least three buttons to make the swap.
    if (buttons_count < 3)
    {
        std::cerr << "Not enough pointer buttons in the system. Need at least 3, "
                  << "while only " << buttons_count << " are defined." << std::endl;
        return 2;
    }

    // According to some internet sources, left and right mouse buttons correspond to
    // codes 1 and 3 respectively. First check that physical left and right buttons
    // are mapped to logical left or right buttons in order not to break the behaviour
    // on systems where left and / or right buttons are used for different purpose.
    if (((pointer_map[0] != 1) && (pointer_map[0] != 3)) ||
        ((pointer_map[2] != 1) && (pointer_map[2] != 3)))
    {
        std::cerr << "A non-standard button mapping detected, automatic swap may be "
                  << "dangerous, use xmodmap to do the swap manually." << std::endl;
        return 3;
    }

    // Now we are good to swap.
    std::swap(pointer_map[0], pointer_map[2]);

    // Set the updated mapping. Note that XSetPointerMapping can return MappingBusy,
    // that indicates, that at least one of the affected buttons is currently in the
    // down state. Mapping is not changed in this case.
    for (int retries = 5; retries > 0; --retries)
    {
        int result = XSetPointerMapping(display, pointer_map, buttons_count);

        switch (result)
        {
        case MappingSuccess:
            return 0;

        case MappingBusy:
            sleep(2);
            continue;

        default:
            std::cerr << "Unable to set pointer mapping. XSetPointerMapping() returned "
                      << result << std::endl;
            return 4;
        }
    }

    // If we reached this part, mapping is not set due to busy pointer button.
    std::cerr << "Unable to set pointer mapping. One of the affected buttons is busy."
              << std::endl;
    return 5;
}
