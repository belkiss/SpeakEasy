INCLUDE_DIRECTORIES(${SpeakEasy_BINARY_DIR}/src)

SET(SpeakEasy_src
    SE_CClock.cpp
    SE_CGUIGLFW.cpp
    #SE_CGUISFML.cpp
    SE_CGUIManager.cpp
    SE_CGUIInterface.cpp
    SE_CLogManager.cpp
    SE_CMemoryManager.cpp
    SE_CStackAllocator.cpp
    main.cpp
)

# list headers (used for MSVC)
SET(SpeakEasy_headers
    SE_CClock.h
    SE_CGUIGLFW.h
    #SE_CGUISFML.h
    SE_CGUIManager.h
    SE_CGUIInterface.h
    SE_CLogManager.h
    SE_CMemoryManager.h
    SE_CStackAllocator.h
    SE_Types.h
)

# executable declaration
# WIN32 allows to set the SUBSYSTEM:WINDOW flag in visual studio
# it is ignored on all platforms other than WIN32
ADD_EXECUTABLE(
    speakeasy WIN32
    ${SpeakEasy_src}
    ${SpeakEasy_headers}
)

# Set the program entry point to main (instead of WinMain)
IF(WIN32)
    SET_TARGET_PROPERTIES(
        speakeasy PROPERTIES
        LINK_FLAGS /ENTRY:"mainCRTStartup"
    )
ENDIF(WIN32)

# linker setup
TARGET_LINK_LIBRARIES(
    speakeasy
    ${OPENGL_LIBRARIES}
    ${OPENGL_glu_LIBRARY}
    ${GLFW_LIBRARY}
    #${SFML_LIBRARIES}
)

INSTALL(TARGETS speakeasy DESTINATION "bin")
