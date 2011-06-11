# needed by the file function
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(SpeakEasy)

# see full compilation lines
SET(CMAKE_VERBOSE_MAKEFILE 0)

# add color on CMake output
SET(CMAKE_COLOR_MAKEFILE ON)

# set the destination of the executable, the CMAKE_BUILD_TYPE is set at launch of cmake executable
# set(EXECUTABLE_OUTPUT_PATH build/${CMAKE_BUILD_TYPE})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# tell cmake to check for custom modules
SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules")


FIND_PACKAGE(OpenGL    REQUIRED)
FIND_PACKAGE(SFML      REQUIRED)
FIND_PACKAGE(PkgConfig REQUIRED)
FIND_PACKAGE(Stlsoft   REQUIRED)
FIND_PACKAGE(Pantheios REQUIRED)

pkg_check_modules(EIGEN3 REQUIRED eigen3)

IF(WIN32)
    SET(CMAKE_CXX_WARNING_LEVEL 4)
ENDIF(WIN32)

IF(UNIX)
    ADD_DEFINITIONS( -Wall -Wextra )
ENDIF(UNIX)

ADD_SUBDIRECTORY(src)
