# needed by the file function
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(SpeakEasy)

LIST(APPEND STARS_MESSAGE "***************")
LIST(APPEND INFO_MESSAGE  "Build SpeakEasy")

# see full compilation lines
# SET(CMAKE_VERBOSE_MAKEFILE 1)

# add color on CMake output
SET(CMAKE_COLOR_MAKEFILE ON)

# set the destination of the executable
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# tell cmake to check for custom modules
SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules")

# Enable c++11
ADD_DEFINITIONS("-std=c++0x")

# Build options
OPTION(BUILD_TESTS "Build Tests"         ON)
OPTION(BUILD_DOC   "Build Documentation" ON)

FIND_PACKAGE(OpenGL REQUIRED)
FIND_PACKAGE(GLFW   REQUIRED)

################################################################################
# Doc
IF(BUILD_DOC)
    # add a target to generate API documentation with Doxygen
    FIND_PACKAGE(Doxygen)

    IF(DOXYGEN_FOUND)
        LIST(APPEND STARS_MESSAGE "*****************")
        LIST(APPEND INFO_MESSAGE  " - Doxygen target")
        CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in
                    ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
        ADD_CUSTOM_TARGET(doc
                        ${DOXYGEN_EXECUTABLE}
                        ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
                        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                        COMMENT "Generating API documentation with Doxygen" VERBATIM
        )
    ENDIF()
ENDIF()
################################################################################

################################################################################
# Enable max compiler debugging output
IF(WIN32)
    SET(CMAKE_CXX_WARNING_LEVEL 4)
ENDIF()

IF(UNIX)
    ADD_DEFINITIONS(-Wall
                    -Wextra
                    -W
                    -Wpadded
                    -Wshadow
                    -Woverloaded-virtual
                    -Wwrite-strings)
ENDIF()
################################################################################

ADD_SUBDIRECTORY(src)

################################################################################
# CPack
SET(CPACK_PACKAGE_VERSION_MAJOR "0")
SET(CPACK_PACKAGE_VERSION_MINOR "0")
SET(CPACK_PACKAGE_VERSION_PATCH "1")

SET(CPACK_SOURCE_GENERATOR "TBZ2")

SET(CPACK_SOURCE_PACKAGE_FILE_NAME
  "${CMAKE_PROJECT_NAME}-${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")

SET(CPACK_SOURCE_IGNORE_FILES "/build/;~$;/.git;kdev;${CPACK_SOURCE_IGNORE_FILES}")

# Must be included *AFTER* setting its properties
INCLUDE(CPack)
################################################################################

################################################################################
# Tests
IF(BUILD_TESTS)
    LIST(APPEND STARS_MESSAGE "*************")
    LIST(APPEND INFO_MESSAGE  " - Unit Tests")
    ENABLE_TESTING()
    ADD_SUBDIRECTORY(tests)
ENDIF()
################################################################################

MESSAGE(STATUS ${STARS_MESSAGE})
MESSAGE(STATUS ${INFO_MESSAGE})
MESSAGE(STATUS ${STARS_MESSAGE})

