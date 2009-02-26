# needed by the file function
cmake_minimum_required(VERSION 2.6)

PROJECT(SpeakEasy)

# set the destination of the executable, the CMAKE_BUILD_TYPE is set at launch of cmake executable
# set(EXECUTABLE_OUTPUT_PATH build/${CMAKE_BUILD_TYPE})
# set(EXECUTABLE_OUTPUT_PATH build)


# Generation of source file list, 1st parameter is the FUNCTION name, second is the cmake list where to store the result, third is the target
file(
    GLOB_RECURSE
    source_files
    src/*
)

#Déclaration de l'exécutable
add_executable(
    speakeasy
    ${source_files}
)

#Configuration de l'édition de liens
target_link_libraries(
    speakeasy
    GL
    GLU
    glut
)