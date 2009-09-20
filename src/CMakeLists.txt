INCLUDE_DIRECTORIES($(SpeakEasy_SOURCE_DIR)/src)

SET(SpeakEasy_src
    SE_Generator.cpp
    SE_Screen.cpp
    uSE_MD5Model.cpp
    uSE_Mesh.cpp
    uSE_Animation.cpp
    uSE_Joint.cpp
    uSE_AnimJoint.cpp
    uSE_Triangle.cpp
    uSE_Weight.cpp
    uSE_Vertex.cpp
    uSE_BoundBox.cpp
    uSE_GLVector.cpp
    misc.cpp
    main.cpp
)

IF(UNIX)
    SET(SFML_LIBS sfml-system sfml-window)
    # create symlink for shaders directory
    EXECUTE_PROCESS(
        COMMAND ${CMAKE_COMMAND} -E create_symlink
        ${CMAKE_SOURCE_DIR}/src/shaders
        ${CMAKE_BINARY_DIR}/shaders
    )
    # create symlink for data/md5 directory
    EXECUTE_PROCESS(
        COMMAND ${CMAKE_COMMAND} -E create_symlink
        ${CMAKE_SOURCE_DIR}/data
        ${CMAKE_BINARY_DIR}/data
    )
ENDIF(UNIX)

IF(WIN32)
    SET(SFML_LIBS sfml-system-d sfml-window-d)
    # copy shaders directory
    EXECUTE_PROCESS(
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/src/shaders
        ${CMAKE_BINARY_DIR}/shaders
    )
    # copy data/md5 directory
    EXECUTE_PROCESS(
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/data
        ${CMAKE_BINARY_DIR}/data
    )

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

IF (NOT SHADERS_DIR)
    SET(SHADERS_DIR ${CMAKE_BINARY_DIR}/shaders)
ENDIF(NOT SHADERS_DIR)
MESSAGE(STATUS "Shaders located in ${SHADERS_DIR}")

IF (NOT MD5_MODELS_DIR)
    SET(MD5_MODELS_DIR ${CMAKE_BINARY_DIR}/data/md5)
ENDIF(NOT MD5_MODELS_DIR)
MESSAGE(STATUS "MD5 files located in ${MD5_MODELS_DIR}")

CONFIGURE_FILE(
    ${CMAKE_SOURCE_DIR}/config.h.cmake
    ${CMAKE_BINARY_DIR}/config.h
)

INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR}
                    ${EIGEN2_INCLUDE_DIR}
                    ${GLIBMM_INCLUDE_DIRS})

# executable declaration
ADD_EXECUTABLE(
    speakeasy
    ${SpeakEasy_src}
)

# linker setup
TARGET_LINK_LIBRARIES(
    speakeasy
    ${OPENGL_LIBRARIES}
    ${OPENGL_glu_LIBRARY}
    ${SFML_LIBS}
    ${GLIBMM_LIBRARIES}
)

INSTALL(TARGETS speakeasy DESTINATION "bin")
