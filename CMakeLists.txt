
CMAKE_MINIMUM_REQUIRED (VERSION 2.8.4)

PROJECT (SwapMouseButtons)

SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Check that one of the officially supported compilers is used.
IF (MSVC)
    MESSAGE (STATUS "Supported compiler used: MSVC")
ELSEIF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    MESSAGE (STATUS "Supported compiler used: GCC")
ELSEIF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    MESSAGE (STATUS "Supported compiler used: Clang")
ELSE ()
    MESSAGE ("Unsupported compiler used: ${CMAKE_CXX_COMPILER_ID}")
ENDIF (MSVC)

SET (SwapMouseButtons_WIN_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/swap_mouse_buttons_win.cpp
)

SET (SwapMouseButtons_UNIX_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/swap_mouse_buttons_unix.cpp
)

# Different approaches (and sources) are used for different platforms, a kludge is used
# to persuade CMake to include all sources in the project and therefore make them visible
# in an IDE but not compilable.
IF (MSVC)
    # See above for the explanation for this kludge.
    SET_SOURCE_FILES_PROPERTIES (${SwapMouseButtons_UNIX_SRCS} PROPERTIES HEADER_FILE_ONLY TRUE)

    # Note that WIN32 key is used to supress the console window.
    ADD_EXECUTABLE (swap_mouse_buttons WIN32
                    ${SwapMouseButtons_WIN_SRCS}
                    ${SwapMouseButtons_UNIX_SRCS}
    )

ELSEIF (UNIX)
    # Boost.ScopeExit is used on linux to ensure resource release.
    FIND_PACKAGE (Boost 1.38 REQUIRED)
    INCLUDE_DIRECTORIES (${Boost_INCLUDE_DIRS})

    # Boost.ScopeExit is used on linux to ensure resource release.
    FIND_PACKAGE (X11 REQUIRED)
    INCLUDE_DIRECTORIES (${X11_X11_INCLUDE_PATH})

    # See above for the explanation for this kludge.
    SET_SOURCE_FILES_PROPERTIES (${SwapMouseButtons_WIN_SRCS} PROPERTIES HEADER_FILE_ONLY TRUE)

    ADD_EXECUTABLE (swap_mouse_buttons
                    ${SwapMouseButtons_WIN_SRCS}
                    ${SwapMouseButtons_UNIX_SRCS}
    )

    TARGET_LINK_LIBRARIES (swap_mouse_buttons
                           ${X11_X11_LIB}
    )

ELSE ()
    MESSAGE ("Cannot generate target for unsupported platform.")

ENDIF (MSVC)

# Add debug postfix for clarity.
SET_TARGET_PROPERTIES (swap_mouse_buttons PROPERTIES DEBUG_POSTFIX "d")
