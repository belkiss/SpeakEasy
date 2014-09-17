# needed by the file function
CMAKE_MINIMUM_REQUIRED(VERSION 2.8.4)

PROJECT(SpeakEasy)

SET(INFO_MESSAGE "Build SpeakEasy")

# see full compilation lines
# SET(CMAKE_VERBOSE_MAKEFILE 1)

# add color on CMake output
SET(CMAKE_COLOR_MAKEFILE ON)

# set the default build type to Debug if no build type is set.
IF(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Debug)
ENDIF()

IF(CMAKE_BUILD_TYPE)
    SET(INFO_MESSAGE "${INFO_MESSAGE} (${CMAKE_BUILD_TYPE})")
ENDIF()

# Add a define to know when we want to compile a debug build
SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DSE_DEBUG")

# set the destination of the executable
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# tell cmake to check for custom modules
SET(CMAKE_MODULE_PATH "${SpeakEasy_SOURCE_DIR}/cmake_modules")

################################################################################
# Build options
OPTION(BUILD_TESTS         "Build Tests"         ON)
OPTION(BUILD_DOCUMENTATION "Build Documentation" ON)

FIND_PACKAGE(OpenGL  REQUIRED)
FIND_PACKAGE(glfw 3  REQUIRED)
FIND_PACKAGE(GLEW    REQUIRED)
FIND_PACKAGE(Threads REQUIRED)

IF(UNIX AND NOT APPLE)
    ############################################################################
    # X11
    FIND_PACKAGE(X11 REQUIRED)
    # Check for XRandR (modern resolution switching and gamma control)
    IF(NOT X11_Xrandr_FOUND)
        MESSAGE(FATAL_ERROR "The RandR library and headers were not found")
    ENDIF()

    # Check for Xinput
    IF(NOT X11_Xinput_FOUND)
        MESSAGE(FATAL_ERROR "The Xinput library and headers were not found")
    ENDIF()

    # Check for Xf86VidMode (fallback gamma control)
    IF(NOT X11_xf86vmode_FOUND)
        MESSAGE(FATAL_ERROR "The Xf86VidMode library and headers were not found")
    ENDIF()

    # Check for Xcursor
    IF(NOT X11_Xcursor_FOUND)
        MESSAGE(FATAL_ERROR "The Xcursor libraries and headers were not found")
    ENDIF()
    ############################################################################
ENDIF()
################################################################################

################################################################################
# Try to determine informations about the version we try to build
FIND_PACKAGE(Git) # OPTIONAL

IF(GIT_FOUND)
    # launch the git binary we just found to get the latest revision SHA1
    EXECUTE_PROCESS(COMMAND ${GIT_EXECUTABLE} log -n 1 --date=short --no-color --format=git\ rev\ %h\ \(%ad\)
                    WORKING_DIRECTORY ${SpeakEasy_SOURCE_DIR}
                    OUTPUT_VARIABLE GIT_INFORMATIONS
                    ERROR_QUIET
                    OUTPUT_STRIP_TRAILING_WHITESPACE)
ENDIF()

IF(NOT GIT_INFORMATIONS)
    # TODO set this information to the packaged version if needed
    SET(GIT_INFORMATIONS "version unknown")
ENDIF()

################################################################################

################################################################################
# Documentation
IF(BUILD_DOCUMENTATION)
    # add a target to generate API documentation with Doxygen
    FIND_PACKAGE(Doxygen)

    IF(DOXYGEN_FOUND)
        SET(INFO_MESSAGE "${INFO_MESSAGE} - Doxygen target")
        CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in
                       ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
        ADD_CUSTOM_TARGET(doc
                          ${DOXYGEN_EXECUTABLE}
                          ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
                          WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                          COMMENT "Generating documentation with Doxygen" VERBATIM)
    ENDIF()
ENDIF()
################################################################################

################################################################################
# Enable max compiler debugging output
IF(MSVC) # Visual Studio
    SET(CMAKE_CXX_WARNING_LEVEL 4)
    # Force it, because most of the time the above line is not enough
    IF(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        STRING(REGEX REPLACE "/W[0-4]" "/W4"
               CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    ELSE()
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    ENDIF()
ENDIF()

IF(UNIX)
    # Enable c++11
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    # Disable RTTI
    ADD_DEFINITIONS(-fno-rtti)
    # Disable Exceptions
    ADD_DEFINITIONS(-fno-exceptions)
    # Enable a LOT of warnings
    ADD_DEFINITIONS(-Wall
                    -Wextra
                    -W
                    -Wpadded
                    -Wshadow
                    -Woverloaded-virtual
                    -Wwrite-strings
                    -Wnon-virtual-dtor
                    -Wunreachable-code)

    # And even more if clang is detected
    IF(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        ADD_DEFINITIONS(-Wdisabled-macro-expansion
                        -Wmissing-variable-declarations
                        -Wglobal-constructors
                        -Wexit-time-destructors
                        -Wextra-semi
                        -Wweak-vtables
                        -Wcovered-switch-default
                        -Wthread-safety-analysis
                        -Wdelete-incomplete
                        -Wnon-pod-varargs
                        -Wreturn-stack-address
                        -Wvexing-parse)
    ENDIF()
ENDIF()
################################################################################

ADD_SUBDIRECTORY(src)

# TODO find a more elegant way to do that...
SET(SHADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/shaders/)

################################################################################
# generate a header file to inform the code of various settings
# set the edit warning message to be inserted in the header
SET(EDIT_WARNING "This file is autogenerated, please do not edit")
CONFIGURE_FILE(${SpeakEasy_SOURCE_DIR}/src/config.h.cmake
               ${SpeakEasy_BINARY_DIR}/src/config.h)
################################################################################

################################################################################
# CPack
SET(CPACK_PACKAGE_VERSION_MAJOR "0")
SET(CPACK_PACKAGE_VERSION_MINOR "0")
SET(CPACK_PACKAGE_VERSION_PATCH "1")

SET(CPACK_SOURCE_GENERATOR "TBZ2")

SET(CPACK_SOURCE_PACKAGE_FILE_NAME
    "${CMAKE_PROJECT_NAME}-${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")

SET(CPACK_SOURCE_IGNORE_FILES
    "/build/;~$;/.git;kdev;${CPACK_SOURCE_IGNORE_FILES}")

# Must be included *AFTER* setting its properties
INCLUDE(CPack)
################################################################################

################################################################################
# Tests
IF(BUILD_TESTS)
    SET(INFO_MESSAGE "${INFO_MESSAGE} - Unit Tests")
    ENABLE_TESTING()
    ADD_SUBDIRECTORY(tests)
ENDIF()
################################################################################

################################################################################
# Status message

# These lines will generate a line of '*' the same length as info_message
STRING(LENGTH ${INFO_MESSAGE} INFO_MESSAGE_LENGTH)
STRING(SUBSTRING
       "***********************************************************************"
       0 ${INFO_MESSAGE_LENGTH}
       STARS_MESSAGE)

MESSAGE(STATUS ${STARS_MESSAGE})
MESSAGE(STATUS ${INFO_MESSAGE})
MESSAGE(STATUS ${STARS_MESSAGE})
################################################################################
