set(SpeakEasy_shaders
	simple_fs.glsl
	simple_vs.glsl
)

foreach(SHADER_FILENAME ${SpeakEasy_shaders})
	MESSAGE(STATUS "Converting ${SHADER_FILENAME} to header")

	# Read as hex the content of the shader file, and put it into the
	# SHADER_BINARY_DATA variable
	file(READ ${SHADER_FILENAME} SHADER_BINARY_DATA HEX)

	# Construct the variable name from the shader name
	string(REGEX REPLACE "\\.glsl" "" SHADER_NAME "${SHADER_FILENAME}")

	# Prefix each hex digit by \x
	string(REGEX REPLACE "(..)" "\\\\x\\1" SHADER_BINARY_DATA "${SHADER_BINARY_DATA}")

	# Jump to next line each 72 characters
	string(REGEX REPLACE
		"(........................................................................)"
		"\\1\"\n    \"" SHADER_BINARY_DATA "${SHADER_BINARY_DATA}")

	# Surround the data with double quotes
	set(SHADER_BINARY_DATA "\"${SHADER_BINARY_DATA}\"")

	# Replace empty double quotes set (if needed)
	string(REGEX REPLACE "\n    \"\"" "" SHADER_BINARY_DATA "${SHADER_BINARY_DATA}")

	set(SHADER_SRC_NAME "${SHADER_NAME}.h")
	LIST(APPEND GENERATED_LIST ${SHADER_SRC_NAME})

	configure_file(glsl_templ.h.in ${SHADER_SRC_NAME})
endforeach()

SET(SpeakEasy_shaders_src ${GENERATED_LIST} PARENT_SCOPE)
