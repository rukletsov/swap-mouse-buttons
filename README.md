# Summary
--------------------------------------------------------------------------------
SwapMouseButtons is a small cross-platform utility that swaps left and right mouse buttons. It can be useful for ambidextrous users and people who learn how to handle the mouse with either hand.

# Dependencies
--------------------------------------------------------------------------------
On Windows the application uses WinAPI, that means only `windows.h` and standard system libraries are required to build and run the application.

On Linux there are slightly more dependencies. This is because the mouse button mapping is managed not by the kernel, but in the X Window System. The application should actually work on an arbitrary Unix, where the following is available:

 * [Boost](http://www.boost.org/). The only library used is header-only ScopeExit. Therefore minimal required version of boost is 1.38.
 * X11. Should be available by default in most Linux distributions and Unix variants.

# Getting Started
--------------------------------------------------------------------------------
No pre-built binaries are currently available. Use the following command to get the source code:

    $ hg clone https://bitbucket.org/rukletsov/swapmousebuttons

CMake is currently used to build the application. On Windows the code is built as a GUI executable to hide the console window.

The code has been successfully built with and run on:

 * openSUSE 12.2 64bit with gcc 4.6.2.
 * openSUSE 12.2 64bit with clang 3.1.
 * Ubuntu 12.04 64bit with gcc 4.6.3.
 * Windows 7 64bit with msvc2010.
