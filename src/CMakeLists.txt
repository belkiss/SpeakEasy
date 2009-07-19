INCLUDE_DIRECTORIES($(SpeakEasy_SOURCE_DIR)/src)

SET(SpeakEasy_src
    uSE_GLMesh.cpp
    uSE_GLTriangle.cpp
    SE_Generator.cpp
    SE_Screen.cpp
    uSE_GLMatrix.cpp
    uSE_GLVector.cpp
    uSE_Quaternion.cpp
    main.cpp
)

IF(WIN32)
    SET(SFML_LIBS sfml-system-d sfml-window-d)
    # copy shaders directory
    EXECUTE_PROCESS(
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/src/shaders
        ${CMAKE_BINARY_DIR}/shaders
    )
ENDIF(WIN32)
IF(UNIX)
    SET(SFML_LIBS sfml-system sfml-window)
    # create symlink for shaders directory
    EXECUTE_PROCESS(
        COMMAND ${CMAKE_COMMAND} -E create_symlink
        ${CMAKE_SOURCE_DIR}/src/shaders
        ${CMAKE_BINARY_DIR}/shaders
    )
    # create symlink for data/obj directory
    EXECUTE_PROCESS(
        COMMAND ${CMAKE_COMMAND} -E create_symlink
        ${CMAKE_SOURCE_DIR}/data
        ${CMAKE_BINARY_DIR}/data
    )
ENDIF(UNIX)

IF (NOT SHADERS_DIR)
    SET(SHADERS_DIR ${CMAKE_BINARY_DIR}/shaders)
ENDIF(NOT SHADERS_DIR)
MESSAGE(STATUS "Shaders located in ${SHADERS_DIR}")

IF (NOT OBJ_MODELS_DIR)
    SET(OBJ_MODELS_DIR ${CMAKE_BINARY_DIR}/data/obj)
ENDIF(NOT OBJ_MODELS_DIR)
MESSAGE(STATUS "OBJ files located in ${OBJ_MODELS_DIR}")

CONFIGURE_FILE(
    ${CMAKE_SOURCE_DIR}/config.h.cmake
    ${CMAKE_BINARY_DIR}/config.h
)

INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR})

# executable declaration
ADD_EXECUTABLE(
    speakeasy
    ${SpeakEasy_src}
)

FIND_PACKAGE(OpenGL)

# linker setup
TARGET_LINK_LIBRARIES(
    speakeasy
    ${OPENGL_LIBRARIES}
    ${OPENGL_glu_LIBRARY}
    ${SFML_LIBS}
)

IF(WIN32)
    # Use the highest warning level for visual studio.
    SET(CMAKE_CXX_WARNING_LEVEL 4)
    IF(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        STRING(REGEX REPLACE "/W[0-4]" "/W4"
        CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    ELSE(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    ENDIF(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    set_target_properties(speakeasy PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE")
    set_target_properties(speakeasy PROPERTIES COMPILE_DEFINITIONS_DEBUG "_CONSOLE")
    set_target_properties(speakeasy PROPERTIES LINK_FLAGS_RELWITHDEBINFO "/SUBSYSTEM:CONSOLE")
    set_target_properties(speakeasy PROPERTIES COMPILE_DEFINITIONS_RELWITHDEBINFO "_CONSOLE")
    set_target_properties(speakeasy PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS")
    set_target_properties(speakeasy PROPERTIES LINK_FLAGS_MINSIZEREL "/SUBSYSTEM:WINDOWS")
ENDIF(WIN32)

INSTALL(TARGETS speakeasy DESTINATION "bin")