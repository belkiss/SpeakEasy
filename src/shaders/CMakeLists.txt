set(SpeakEasy_shaders
    simple_fs.glsl
    simple_vs.glsl
)

foreach(SHADER_FILENAME ${SpeakEasy_shaders})

    # Get the shader filename without the extension
    get_filename_component(SHADER_NAME ${SHADER_FILENAME} NAME_WE)

    # Construct the header file full path
    set(SHADER_NAME "${CMAKE_CURRENT_BINARY_DIR}/${SHADER_NAME}.h")

    list(APPEND GENERATED_LIST ${SHADER_NAME})

    add_custom_command(OUTPUT  ${SHADER_NAME}
                       COMMAND ${CMAKE_COMMAND} -DSHADER_FILENAME=${SHADER_FILENAME}
                                     -DOUTPUT_FOLDER=${CMAKE_CURRENT_BINARY_DIR}
                                     -P shader_to_header.cmake
                       DEPENDS ${SHADER_FILENAME}
                       WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endforeach()

add_custom_target(${SHADER_TO_HEADER} DEPENDS ${GENERATED_LIST})

SET(SpeakEasy_shaders_src ${GENERATED_LIST} PARENT_SCOPE)
