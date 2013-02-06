INCLUDE_DIRECTORIES(${SpeakEasy_BINARY_DIR}/src)
INCLUDE_DIRECTORIES(${GLFW_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${GLEW_INCLUDE_PATH})

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

# list dependencies
SET(SpeakEasy_Libs
    ${OPENGL_LIBRARIES}
    ${OPENGL_glu_LIBRARY}
    ${GLFW_LIBRARY}
    ${GLEW_LIBRARY}
)

IF(GLFW_IS_STATIC)
    LIST(APPEND SpeakEasy_Libs
         ${X11_Xxf86vm_LIB}
         ${X11_Xrandr_LIB}
         rt
    )
ENDIF()

# executable declaration
SET(Executable_name speakeasy)
# WIN32 allows to set the SUBSYSTEM:WINDOW flag in visual studio
# it is ignored on all platforms other than WIN32
ADD_EXECUTABLE(
    ${Executable_name} WIN32
    ${SpeakEasy_src}
    ${SpeakEasy_headers}
)

# Set the program entry point to main (instead of WinMain)
IF(WIN32)
    SET_TARGET_PROPERTIES(
        ${Executable_name} PROPERTIES
        PROJECT_LABEL ${PROJECT_NAME}
        LINK_FLAGS /ENTRY:"mainCRTStartup"
    )
ENDIF()

# linker setup
TARGET_LINK_LIBRARIES(
    ${Executable_name}
    ${SpeakEasy_Libs}
)

INSTALL(TARGETS speakeasy DESTINATION "bin")
