# needed by the file function
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(SpeakEasy)

# to see command line of gcc
SET(CMAKE_VERBOSE_MAKEFILE 0)
# to add Color on CMake Process
SET(CMAKE_COLOR_MAKEFILE ON)

# set the destination of the executable, the CMAKE_BUILD_TYPE is set at launch of cmake executable
# set(EXECUTABLE_OUTPUT_PATH build/${CMAKE_BUILD_TYPE})
# set(EXECUTABLE_OUTPUT_PATH build)

IF(WIN32)
    SET(CMAKE_CXX_WARNING_LEVEL 4)
ENDIF(WIN32)
IF(UNIX)
    ADD_DEFINITIONS( -Wall -Wextra )
ENDIF(UNIX)

# Generation of source file list, 1st parameter is the FUNCTION name, second is the cmake list where to store the result, third is the target
FILE(
    GLOB_RECURSE
    source_files
    src/*
)

# executable declaration
ADD_EXECUTABLE(
    speakeasy
    ${source_files}
)

# create symlink for shaders directory
EXECUTE_PROCESS(
    COMMAND ${CMAKE_COMMAND} -E create_symlink
    ${CMAKE_SOURCE_DIR}/src/shaders
    ${CMAKE_BINARY_DIR}/shaders
)

# linker setup
TARGET_LINK_LIBRARIES(
    speakeasy
    GL
    GLU
    sfml-system
    sfml-window
)
