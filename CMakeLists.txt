
CMAKE_MINIMUM_REQUIRED (VERSION 2.8.4)

PROJECT (MouseButtonSwap)

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

SET (MouseButtonSwap_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/swap_mouse_buttons_win.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/swap_mouse_buttons_unix.cpp
)

# Different code is used for different platforms.
IF (MSVC)
    # Make files for other platforms visible, but not compilable.
    SET_SOURCE_FILES_PROPERTIES (${CMAKE_CURRENT_SOURCE_DIR}/swap_mouse_buttons_unix.cpp
            PROPERTIES HEADER_FILE_ONLY TRUE)

    # Note that WIN32 key is used to supress the console window.
    ADD_EXECUTABLE (swap_mouse_buttons WIN32
					${MouseButtonSwap_SRCS}
    )

    # Supress secure warnings (C4996) for MSVC compiler.
    SET_TARGET_PROPERTIES (swap_mouse_buttons PROPERTIES COMPILE_FLAGS
                           "/D _CRT_SECURE_NO_DEPRECATE /D _SCL_SECURE_NO_WARNINGS")

ELSEIF (UNIX)

    # Make files for other platforms visible, but not compilable.
    SET_SOURCE_FILES_PROPERTIES (${CMAKE_CURRENT_SOURCE_DIR}/swap_mouse_buttons_win.cpp
        PROPERTIES HEADER_FILE_ONLY TRUE)

    ADD_EXECUTABLE (swap_mouse_buttons
					${MouseButtonSwap_SRCS}
    )

    TARGET_LINK_LIBRARIES (swap_mouse_buttons
                           X11
    )

ELSE ()
    MESSAGE ("Cannot generate target for unsupported platform.")

ENDIF (MSVC)

# Add debug postfix for clarity.
SET_TARGET_PROPERTIES (swap_mouse_buttons PROPERTIES DEBUG_POSTFIX "d")
