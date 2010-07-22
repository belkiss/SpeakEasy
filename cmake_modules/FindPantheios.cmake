#----------------------------------------------------------------------------------
# (C) 2009 Sergey Nikulov
# (C) 2010 Lambert CLARA
#
# Usage as follows:
#  - just add FIND_PACKAGE(Pantheios) in your CMakeLists.txt, then check variables
#----------------------------------------------------------------------------------
# PANTHEIOS_FOUND       - TRUE/FALSE - Found/not found
# PANTHEIOS_INCLUDE_DIR - path to include
# PANTHEIOS_VER_MAJOR
# PANTHEIOS_VER_MINOR
# PANTHEIOS_VER_REVISION
#----------------------------------------------------------------------------------
# TODO: need to implement FIND_PACKAGE(Pantheios [here required version string])
#----------------------------------------------------------------------------------

SET(PANTHEIOS_FOUND "NO")

# try get environment var first...
SET(_PANTHEIOS_ROOT $ENV{FASTFORMAT_ROOT})

IF(_PANTHEIOS_ROOT)
    # add include folder to ENVIRONMENT path...
    FILE(TO_CMAKE_PATH ${_PANTHEIOS_ROOT} _PANTHEIOS_ROOT)
    SET(PANTHEIOS_INCLUDE_DIR ${_PANTHEIOS_ROOT}/include)
ELSE(_PANTHEIOS_ROOT)
    # try to find in well known for CMake includes
    FIND_PATH(PANTHEIOS_INCLUDE_DIR pantheios/pantheios.h)
ENDIF(_PANTHEIOS_ROOT)


IF(PANTHEIOS_INCLUDE_DIR)
    FILE(READ "${PANTHEIOS_INCLUDE_DIR}/pantheios/pantheios.h" _pantheios_h_CONTENT)
    STRING(REGEX REPLACE ".*#define[ ]+PANTHEIOS_VER_MAJOR[ ]+([0-9]+).*" "\\1" PANTHEIOS_VER_MAJOR "${_pantheios_h_CONTENT}")
    STRING(REGEX REPLACE ".*#define[ ]+PANTHEIOS_VER_MINOR[ ]+([0-9]+).*" "\\1" PANTHEIOS_VER_MINOR "${_pantheios_h_CONTENT}")
    STRING(REGEX REPLACE ".*#define[ ]+PANTHEIOS_VER_REVISION[ ]+([0-9]+).*" "\\1" PANTHEIOS_VER_REVISION "${_pantheios_h_CONTENT}")

    # ugly hack to get the library directory
    SET(PANTHEIOS_LIBRARY_DIR ${PANTHEIOS_INCLUDE_DIR}/../lib)

    # Look for the libraries.
    FIND_LIBRARY(PANTHEIOS_CORE_LIBRARY     NAMES pantheios.1.core.gcc44.mt.debug        PATHS ${PANTHEIOS_LIBRARY_DIR})
    FIND_LIBRARY(PANTHEIOS_UTIL_LIBRARY     NAMES pantheios.1.util.gcc44.mt.debug        PATHS ${PANTHEIOS_LIBRARY_DIR})
    FIND_LIBRARY(PANTHEIOS_FE_LIBRARY       NAMES pantheios.1.fe.all.gcc44.mt.debug      PATHS ${PANTHEIOS_LIBRARY_DIR})
    FIND_LIBRARY(PANTHEIOS_BE_FILE_LIBRARY  NAMES pantheios.1.be.fprintf.gcc44.mt.debug  PATHS ${PANTHEIOS_LIBRARY_DIR})
    FIND_LIBRARY(PANTHEIOS_BEC_FILE_LIBRARY NAMES pantheios.1.bec.fprintf.gcc44.mt.debug PATHS ${PANTHEIOS_LIBRARY_DIR})

    LIST(APPEND PANTHEIOS_LIBRARY ${PANTHEIOS_CORE_LIBRARY})
    LIST(APPEND PANTHEIOS_LIBRARY ${PANTHEIOS_UTIL_LIBRARY})
    LIST(APPEND PANTHEIOS_LIBRARY ${PANTHEIOS_FE_LIBRARY})
    LIST(APPEND PANTHEIOS_LIBRARY ${PANTHEIOS_BE_FILE_LIBRARY})
    LIST(APPEND PANTHEIOS_LIBRARY ${PANTHEIOS_BEC_FILE_LIBRARY})
ENDIF(PANTHEIOS_INCLUDE_DIR)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(Pantheios DEFAULT_MSG PANTHEIOS_INCLUDE_DIR PANTHEIOS_LIBRARY)


MARK_AS_ADVANCED(
    PANTHEIOS_INCLUDE_DIR
    PANTHEIOS_VER_MAJOR
    PANTHEIOS_VER_MINOR
    PANTHEIOS_VER_REVISION
    )
