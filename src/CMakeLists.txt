
SET(SpeakEasy_src
    SE_CGUIGLFW.cpp
    SE_CGUIManager.cpp
    SE_CGUIInterface.cpp
    SE_CLogManager.cpp
    SE_CMemoryManager.cpp
    SE_CStackAllocator.cpp
    main.cpp
)

# executable declaration
ADD_EXECUTABLE(
    speakeasy
    ${SpeakEasy_src}
)

# linker setup
TARGET_LINK_LIBRARIES(
    speakeasy
    ${GLFW_LIBRARY}
)

INSTALL(TARGETS speakeasy DESTINATION "bin")
