
SET(SpeakEasy_src
    SE_CGUIGLFW.cpp
    SE_CGUIManager.cpp
    SE_CGUIInterface.cpp
    SE_CLogManager.cpp
    SE_CMemoryManager.cpp
    SE_CStackAllocator.cpp
    main.cpp
)

# list headers (used for VS)
SET(SpeakEasy_headers
    SE_CGUIGLFW.h
    SE_CGUIManager.h
    SE_CGUIInterface.h
    SE_CLogManager.h
    SE_CMemoryManager.h
    SE_CStackAllocator.h
    SE_Types.h
)

# executable declaration
ADD_EXECUTABLE(
    speakeasy
    ${SpeakEasy_src}
    ${SpeakEasy_headers}
)

# linker setup
TARGET_LINK_LIBRARIES(
    speakeasy
    ${OPENGL_LIBRARIES}
    ${OPENGL_glu_LIBRARY}
    ${GLFW_LIBRARY}
)

INSTALL(TARGETS speakeasy DESTINATION "bin")
