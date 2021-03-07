INCLUDE_DIRECTORIES(${SpeakEasy_BINARY_DIR}/src)

SET(SHADER_TO_HEADER "shader_to_header")
ADD_SUBDIRECTORY(shaders)

SET(SpeakEasy_src
    SE_CClock.cpp
    SE_CGUIGLFW.cpp
    SE_CGUIManager.cpp
    SE_CGUIInterface.cpp
    SE_CLogManager.cpp
    SE_CMemoryManager.cpp
    SE_CRenderManager.cpp
    SE_CStackAllocator.cpp
    SE_IBaseManager.cpp
    main.cpp
)

# list headers (used for MSVC)
SET(SpeakEasy_headers
    SE_CClock.h
    SE_CGUIGLFW.h
    SE_CGUIManager.h
    SE_CGUIInterface.h
    SE_CLogManager.h
    SE_CMemoryManager.h
    SE_CRenderManager.h
    SE_CStackAllocator.h
    SE_IBaseManager.h
    SE_Types.h
    config.h.cmake
    config.h # generated from the above file
)

# list shaders
SET(SpeakEasy_shaders
    shaders/simple_fs.glsl
    shaders/simple_vs.glsl
)

# list dependencies
SET(SpeakEasy_Libs
    ${OPENGL_LIBRARIES}
    ${OPENGL_glu_LIBRARY}
    glfw
    glew_s
)

# Apple considers the whole OpenGL API deprecated
IF (APPLE)
    ADD_DEFINITIONS (-DGL_SILENCE_DEPRECATION)
ENDIF()

# executable declaration
SET(Executable_name speakeasy)
# WIN32 allows to set the SUBSYSTEM:WINDOW flag in visual studio
# it is ignored on all platforms other than WIN32
ADD_EXECUTABLE(
    ${Executable_name} WIN32
    ${SpeakEasy_src}
    ${SpeakEasy_headers}
    ${SpeakEasy_shaders}
)

# Add the shader conversion custom command to the dependencies
ADD_DEPENDENCIES(${Executable_name} ${SHADER_TO_HEADER})

# Set the program entry point to main (instead of WinMain)
IF(WIN32)
    SET_TARGET_PROPERTIES(
        ${Executable_name} PROPERTIES
        PROJECT_LABEL ${PROJECT_NAME}
        LINK_FLAGS /ENTRY:"mainCRTStartup"
    )
ENDIF()

# pch setup
TARGET_PRECOMPILE_HEADERS(
    ${Executable_name}
    PRIVATE
    "${SpeakEasy_SOURCE_DIR}/src/SE_Types.h"
)

# linker setup
TARGET_LINK_LIBRARIES(
    ${Executable_name}
    ${SpeakEasy_Libs}
)

INSTALL(TARGETS speakeasy DESTINATION "bin")
