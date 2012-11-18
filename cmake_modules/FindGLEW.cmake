#
# Try to find GLEW library and include path.
# Once done this will define
#
# GLEW_FOUND
# GLEW_INCLUDE_PATH
# GLEW_LIBRARY
#



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

    STRING(REGEX MATCH "Win64" ISWIN64 ${CMAKE_GENERATOR})
    IF("${ISWIN64}" STREQUAL "Win64")
        SET(GLEW_LIB_NAMES glew64 glew64s glew32 glew32s) # check the name of glew lib on 64...
    ELSE()
        SET(GLEW_LIB_NAMES glew32 glew32s)
    ENDIF()

    FIND_PATH(GLEW_INCLUDE_PATH GL/glew.h
              DOC "The directory where GL/glew.h resides"
              $ENV{PROGRAMFILES}/GLEW/include
              ${VS_DIR}/VC/include
    )

    FIND_LIBRARY(GLEW_LIBRARY NAMES glew ${GLEW_LIB_NAMES}
                 DOC "The GLEW library"
                 PATHS
                 $ENV{PROGRAMFILES}/GLEW/lib
                 ${VS_DIR}/VC/lib
    )
ELSE()
    FIND_PATH( GLEW_INCLUDE_PATH GL/glew.h
        /usr/include
        /usr/local/include
        /sw/include
        /opt/local/include
        $ENV{NVSDKCOMPUTE_ROOT}/shared/inc
        DOC "The directory where GL/glew.h resides")
    FIND_LIBRARY( GLEW_LIBRARY
        NAMES GLEW glew
        PATHS
        /usr/lib64
        /usr/lib
        /usr/local/lib64
        /usr/local/lib
        /sw/lib
        /opt/local/lib
        $ENV{NVSDKCOMPUTE_ROOT}/shared/lib/linux
        DOC "The GLEW library")
ENDIF()

IF(GLEW_INCLUDE_PATH)
    SET(GLEW_FOUND 1 CACHE STRING "Set to 1 if GLEW is found, 0 otherwise")
ELSE()
    SET(GLEW_FOUND 0 CACHE STRING "Set to 1 if GLEW is found, 0 otherwise")
ENDIF()

# handle the QUIETLY and REQUIRED arguments and set GLEW_FOUND to TRUE if
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GLEW DEFAULT_MSG GLEW_LIBRARY)
