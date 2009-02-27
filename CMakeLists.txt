# needed by the file function
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(SpeakEasy)

# set the destination of the executable, the CMAKE_BUILD_TYPE is set at launch of cmake executable
# set(EXECUTABLE_OUTPUT_PATH build/${CMAKE_BUILD_TYPE})
# set(EXECUTABLE_OUTPUT_PATH build)

ADD_DEFINITIONS( -Wall )
# ADD_DEFINITIONS(-DQT_NO_DEBUG)

FIND_PACKAGE( Qt4 REQUIRED )
SET(QT_USE_QTOPENGL 1)
INCLUDE(${QT_USE_FILE})

# Generation of source file list, 1st parameter is the FUNCTION name, second is the cmake list where to store the result, third is the target
FILE(
    GLOB_RECURSE
    source_files
    src/*
)

FILE(
    GLOB_RECURSE
    SPEAKEASY_MOC_HDRS
    src/*.h
)

QT4_WRAP_CPP(SPEAKEASY_MOC_SRCS ${SPEAKEASY_MOC_HDRS})

# executable declaration
ADD_EXECUTABLE(
    speakeasy
    ${source_files}
    ${SPEAKEASY_MOC_SRCS}
)

# linker setup
TARGET_LINK_LIBRARIES(
    speakeasy
    GL
    GLU
    ${QT_LIBRARIES}
)
