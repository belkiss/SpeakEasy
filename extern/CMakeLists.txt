################################################################################
# GLFW 
SET(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "")
SET(GLFW_BUILD_TESTS    OFF CACHE BOOL "")
SET(GLFW_BUILD_DOCS     OFF CACHE BOOL "")
SET(GLFW_INSTALL        OFF CACHE BOOL "")

ADD_SUBDIRECTORY(glfw)
################################################################################

################################################################################
# GLEW
SET(glew-cmake_BUILD_SHARED         OFF CACHE BOOL "")
SET(glew-cmake_BUILD_MULTI_CONTEXT  OFF CACHE BOOL "")

ADD_SUBDIRECTORY(glew)
################################################################################
