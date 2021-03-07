################################################################################
# GLFW
SET(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "")
SET(GLFW_BUILD_TESTS    OFF CACHE BOOL "")
SET(GLFW_BUILD_DOCS     OFF CACHE BOOL "")
SET(GLFW_INSTALL        OFF CACHE BOOL "")

ADD_SUBDIRECTORY(glfw/src)
################################################################################

################################################################################
# GLEW
SET(BUILD_SHARED_LIBS OFF CACHE BOOL "")
SET(BUILD_UTILS       OFF CACHE BOOL "")
ADD_SUBDIRECTORY(glew/src/build/cmake)
################################################################################
