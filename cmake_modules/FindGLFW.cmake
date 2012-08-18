# http://projects.coderbasement.com/repositories/entry/sandbox/ifsic/mar/tp1/FindGLFW.cmake
# http://gitorious.org/siege/siege/blobs/master/CMakeModules/FindGLFW.cmake
# https://github.com/ptrv/cmake_modules/blob/master/FindGLFW.cmake
# http://gdx.hg.sourceforge.net/hgweb/gdx/gdx/file/8752195008a7/cmake/Modules/FindGLFW.cmake

# Locate GLFW includes and library
# This module defines
#   GLFW_FOUND, if false, do not try to link to GLFW
#   GLFW_INCLUDE_DIR, the path where GLFW headers are located(the directory containing the glfw.h file)
#   GLFW_LIBRARY, libraries to link against to use GLFW
#   GLFW_IS_STATIC, (on *nix only) true if the found glfw library is static
#
# $GLFWDIR is an environment variable that would correspond
# to the prefix used to configure GLFW.
#
# By default, the dynamic library of GLFW will be found. To find the static one instead,
# you must set the GLFW_STATIC_LIBRARY variable to TRUE before calling find_package(GLFW ...).
#
# Created by Olivier Delannoy. This was influenced by
# FindOpenAL.cmake module. MACOSX is not yet handled correctly

IF(WIN32)
    IF(MSVC11)
        GET_FILENAME_COMPONENT(VS_DIR [HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\VisualStudio\\11.0\\Setup\\VS;ProductDir] REALPATH CACHE)
    ELSEIF(MSVC10)
        GET_FILENAME_COMPONENT(VS_DIR [HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\VisualStudio\\10.0\\Setup\\VS;ProductDir] REALPATH CACHE)
    ELSEIF(MSVC90)
        GET_FILENAME_COMPONENT(VS_DIR [HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\VisualStudio\\9.0\\Setup\\VS;ProductDir] REALPATH CACHE)
    ELSEIF(MSVC80)
        GET_FILENAME_COMPONENT(VS_DIR [HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\VisualStudio\\8.0\\Setup\\VS;ProductDir] REALPATH CACHE)
    ENDIF()
    MESSAGE(STATUS "Found MS in " ${VS_DIR})
ENDIF()

# find the GLFW include directory
FIND_PATH(GLFW_INCLUDE_DIR  NAMES GL/glfw.h GL/glfw3.h
                            DOC "Path to GLFW header."
                            PATH_SUFFIXES include
                            PATHS
                            ~/Library/Frameworks
                            /Library/Frameworks
                            ~/Library/Frameworks/GLFW.framework/Headers
                            /Library/Frameworks/GLFW.framework.Headers # Tiger
                            /usr/local/X11R6/
                            /usr/local/
                            /usr
                            /usr/X11R6/
                            /usr/X11/
                            /usr/include/X11
                            /opt/X11/include
                            /sw          # Fink
                            /opt/local/  # DarwinPorts
                            /opt/csw/    # Blastwave
                            /opt/
                            ${VS_DIR}/VC/include
                            ${GLFWDIR}
                            $ENV{GLFWDIR}
)

IF(GLFW_INCLUDE_DIR)
    IF(EXISTS ${GLFW_INCLUDE_DIR}/GL/glfw.h)
        SET(GLFW_INCLUDE_FILE "glfw.h")
    ELSE()
        IF(EXISTS ${GLFW_INCLUDE_DIR}/GL/glfw3.h)
            SET(GLFW_INCLUDE_FILE "glfw3.h")
        ENDIF()
    ENDIF()

    # TODO: check the version number
    SET(GLFW_VERSION_OK TRUE)
    # GLFW_FIND_VERSION AND

    # extract the major and minor version numbers from GL/glfw.h
    FILE(STRINGS "${GLFW_INCLUDE_DIR}/GL/${GLFW_INCLUDE_FILE}" GLFW_H REGEX "^.*API version: .*$")

    STRING(REGEX REPLACE "^.*API version: ([0-9]+).*$" "\\1"          GLFW_VERSION_MAJOR "${GLFW_H}")
    STRING(REGEX REPLACE "^.*API version: [0-9]+\\.([0-9]+).*$" "\\1" GLFW_VERSION_MINOR "${GLFW_H}")

#     math(EXPR GLFW_REQUESTED_VERSION "${GLFW_FIND_VERSION_MAJOR} * 10 + ${GLFW_FIND_VERSION_MINOR}")
#
#     # if we could extract them, compare with the requested version number
#     if (GLFW_VERSION_MAJOR)
#         # transform version numbers to an integer
#         math(EXPR GLFW_VERSION "${GLFW_VERSION_MAJOR} * 10 + ${GLFW_VERSION_MINOR}")
#
#         # compare them
#         if(GLFW_VERSION LESS GLFW_REQUESTED_VERSION)
#             set(GLFW_VERSION_OK FALSE)
#         endif()
#     else()
#         # GLFW version is < 2.0
#         if (GLFW_REQUESTED_VERSION GREATER 19)
#             set(GLFW_VERSION_OK FALSE)
#         endif()
#     endif()

    FIND_LIBRARY(GLFW_LIBRARY   NAMES glfw glfw3
                                PATHS
                                ~/Library/Frameworks
                                /Library/Frameworks
                                /usr/local
                                /usr/local/X11R6
                                /usr/X11R6
                                /usr/X11
                                /usr/lib/X11
                                /usr
                                /opt/local
                                /opt/csw
                                /opt/X11
                                /opt
                                /sw
                                $ENV{GLFWDIR}/support/msvc80/Debug
                                $ENV{GLFWDIR}/support/msvc80/Release
                                ${VS_DIR}/VC/lib
                                ${GLFWDIR}
                                $ENV{GLFWDIR}
    )

    IF(GLFW_LIBRARY)
        SET(GLFW_FOUND TRUE)
        IF(GLFW_LIBRARY MATCHES ".a$")
            SET(GLFW_IS_STATIC TRUE)
        ENDIF()
    ELSE()
        MESSAGE("libglfw[3] could not be found")
    ENDIF()
ELSE()
    MESSAGE("glfw.h and glfw3.h could not be found")
ENDIF()

IF(GLFW_FOUND)
    IF(NOT GLFW_FIND_QUIETLY)
        MESSAGE(STATUS "Found GLFW version ${GLFW_VERSION_MAJOR}.${GLFW_VERSION_MINOR}")
    ENDIF()
ELSE()
    IF(GLFW_FIND_REQUIRED)
        MESSAGE(FATAL_ERROR "Could not find GLFW")
    ENDIF()
ENDIF()
