#----------------------------------------------------------------------------------
# (C) 2009 Sergey Nikulov
# (C) 2010 Lambert CLARA
#
# Usage as follows:
#  - just add FIND_PACKAGE(Stlsoft) in your CMakeLists.txt, then check variables
#----------------------------------------------------------------------------------
# STLSOFT_FOUND       - TRUE/FALSE - Found/not found
# STLSOFT_INCLUDE_DIR - path to include
# STLSOFT_VER_MAJOR
# STLSOFT_VER_MINOR
# STLSOFT_VER_REVISION
#----------------------------------------------------------------------------------
# TODO: need to implement FIND_PACKAGE(Stlsoft [here required version string])
#----------------------------------------------------------------------------------

SET(STLSOFT_FOUND "NO")

# try get environment var first...
SET(_STLSOFT_ROOT $ENV{STLSOFT})

IF(_STLSOFT_ROOT)
    # add include folder to ENVIRONMENT path...
    FILE(TO_CMAKE_PATH ${_STLSOFT_ROOT} _STLSOFT_ROOT)
    SET(STLSOFT_INCLUDE_DIR ${_STLSOFT_ROOT}/include)
ELSE(_STLSOFT_ROOT)
    # try to find in well known for CMake includes
    FIND_PATH(STLSOFT_INCLUDE_DIR stlsoft/stlsoft.h)
ENDIF(_STLSOFT_ROOT)

IF(STLSOFT_INCLUDE_DIR)
    FILE(READ "${STLSOFT_INCLUDE_DIR}/stlsoft/stlsoft.h" _stlsoft_h_CONTENT)
    STRING(REGEX REPLACE ".*#define[ ]+_STLSOFT_VER_MAJOR[ ]+([0-9]+).*" "\\1" STLSOFT_VER_MAJOR "${_stlsoft_h_CONTENT}")
    STRING(REGEX REPLACE ".*#define[ ]+_STLSOFT_VER_MINOR[ ]+([0-9]+).*" "\\1" STLSOFT_VER_MINOR "${_stlsoft_h_CONTENT}")
    STRING(REGEX REPLACE ".*#define[ ]+_STLSOFT_VER_REVISION[ ]+([0-9]+).*" "\\1" STLSOFT_VER_REVISION "${_stlsoft_h_CONTENT}")
endif(STLSOFT_INCLUDE_DIR)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(Stlsoft DEFAULT_MSG STLSOFT_INCLUDE_DIR)


MARK_AS_ADVANCED(
    STLSOFT_INCLUDE_DIR
    STLSOFT_VER_MAJOR
    STLSOFT_VER_MINOR
    STLSOFT_VER_REVISION
    )
