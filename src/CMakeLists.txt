INCLUDE_DIRECTORIES(${SpeakEasy_BINARY_DIR}/src)
INCLUDE_DIRECTORIES(${GLFW3_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${GLEW_INCLUDE_DIR})

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
    ${GLFW3_LIBRARY}
    ${GLEW_LIBRARY}
    ${CMAKE_THREAD_LIBS_INIT}
)

IF(UNIX AND NOT APPLE)
    LIST(APPEND SpeakEasy_Libs
         ${X11_Xrandr_LIB}
         ${X11_Xinput_LIB}
         ${X11_Xxf86vm_LIB}
         ${X11_Xcursor_LIB}
         ${X11_X11_LIB}
         ${X11_Xinerama_LIB}
         ${CMAKE_DL_LIBS}
    )
ELSEIF(APPLE)
    # Set up library and include paths
    FIND_LIBRARY(COCOA_FRAMEWORK Cocoa)
    FIND_LIBRARY(IOKIT_FRAMEWORK IOKit)
    FIND_LIBRARY(CARBON_FRAMEWORK Carbon)
    FIND_LIBRARY(CORE_FOUNDATION_FRAMEWORK CoreFoundation)
    FIND_LIBRARY(CORE_VIDEO_FRAMEWORK CoreVideo)
    LIST(APPEND SpeakEasy_Libs ${COCOA_FRAMEWORK}
                               ${OPENGL_gl_LIBRARY}
                               ${IOKIT_FRAMEWORK}
                               ${CORE_FOUNDATION_FRAMEWORK}
                               ${CORE_VIDEO_FRAMEWORK}
                               ${CARBON_FRAMEWORK})
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

# Force include the header containing the types into all the others
SET_TARGET_PROPERTIES(
    ${Executable_name} PROPERTIES
    COMPILE_FLAGS "-include ${SpeakEasy_SOURCE_DIR}/src/SE_Types.h")

# linker setup
TARGET_LINK_LIBRARIES(
    ${Executable_name}
    ${SpeakEasy_Libs}
)

INSTALL(TARGETS speakeasy DESTINATION "bin")
