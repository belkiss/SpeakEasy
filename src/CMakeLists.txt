INCLUDE_DIRECTORIES(${SpeakEasy_BINARY_DIR}/src)

SET(SpeakEasy_src
    SE_CClock.cpp
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
    SE_CGUIManager.h
    SE_CGUIInterface.h
    SE_CLogManager.h
    SE_CMemoryManager.h
    SE_CStackAllocator.h
    SE_Types.h
    config.h.cmake
    config.h # generated from the above file
)

IF(USE_GLFW)
    LIST(APPEND SpeakEasy_src
         SE_CGUIGLFW.cpp
    )
    LIST(APPEND SpeakEasy_headers
         SE_CGUIGLFW.h
    )
ELSEIF(USE_SFML)
    LIST(APPEND SpeakEasy_src
         SE_CGUISFML.cpp
    )
    LIST(APPEND SpeakEasy_headers
         SE_CGUISFML.h
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
ENDIF(WIN32)

# linker setup
TARGET_LINK_LIBRARIES(
    ${Executable_name}
    ${OPENGL_LIBRARIES}
    ${OPENGL_glu_LIBRARY}
    ${GLFW_LIBRARY}
    ${SFML_LIBRARIES}
)

INSTALL(TARGETS speakeasy DESTINATION "bin")
