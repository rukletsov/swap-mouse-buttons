
#include "windows.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    // Get current state.
    int is_swapped = GetSystemMetrics(SM_SWAPBUTTON);

    // Swap buttons. Return code is rather useless here.
    SwapMouseButton(!is_swapped);

    return 0;
}
