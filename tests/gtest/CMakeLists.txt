# Find googletest or retrieve it from web
FIND_PACKAGE(GTest QUIET)
IF(NOT GTEST_FOUND)
    INCLUDE(ExternalProject)

    SET(gtest_debuglibs_dir   DebugLibs)
    SET(gtest_releaselibs_dir ReleaseLibs)

    SET(gtest_CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -DCMAKE_OSX_ARCHITECTURES=${CMAKE_OSX_ARCHITECTURES}
        -DCMAKE_DEBUG_POSTFIX=d
        -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG:PATH=${gtest_debuglibs_dir}
        -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE:PATH=${gtest_releaselibs_dir}
        -DCMAKE_CXX_FLAGS=-D_VARIADIC_MAX=10
        -Dgtest_force_shared_crt=ON
        -Dgtest_disable_pthreads=ON
    )

    ExternalProject_Add(googletest
        PREFIX          ${CMAKE_CURRENT_BINARY_DIR}
        URL             http://googletest.googlecode.com/files/gtest-1.7.0.zip
        URL_MD5         2D6EC8CCDF5C46B05BA54A9FD1D130D7
        TIMEOUT         60
        CMAKE_ARGS      ${gtest_CMAKE_ARGS}
        INSTALL_COMMAND ""
    )

    ExternalProject_Get_Property(googletest source_dir)
    ExternalProject_Get_Property(googletest binary_dir)

    SET(GTEST_LIBRARY            ${binary_dir}/${gtest_releaselibs_dir}/${CMAKE_STATIC_LIBRARY_PREFIX}gtest${CMAKE_STATIC_LIBRARY_SUFFIX}     )
    SET(GTEST_MAIN_LIBRARY       ${binary_dir}/${gtest_releaselibs_dir}/${CMAKE_STATIC_LIBRARY_PREFIX}gtest_main${CMAKE_STATIC_LIBRARY_SUFFIX})
    SET(GTEST_LIBRARY_DEBUG      ${binary_dir}/${gtest_debuglibs_dir}/${CMAKE_STATIC_LIBRARY_PREFIX}gtestd${CMAKE_STATIC_LIBRARY_SUFFIX}      )
    SET(GTEST_MAIN_LIBRARY_DEBUG ${binary_dir}/${gtest_debuglibs_dir}/${CMAKE_STATIC_LIBRARY_PREFIX}gtest_maind${CMAKE_STATIC_LIBRARY_SUFFIX} )

    IF(CMAKE_BUILD_TYPE MATCHES Release)
        SET(GTEST_LIBRARIES      ${GTEST_LIBRARY})
        SET(GTEST_MAIN_LIBRARIES ${GTEST_MAIN_LIBRARY})
    ELSE()
        SET(GTEST_LIBRARIES      ${GTEST_LIBRARY_DEBUG})
        SET(GTEST_MAIN_LIBRARIES ${GTEST_MAIN_LIBRARY_DEBUG})
    ENDIF()

    SET(GTEST_FOUND          TRUE)
    SET(GTEST_INCLUDE_DIRS   ${source_dir}/include)
    SET(GTEST_BOTH_LIBRARIES ${GTEST_LIBRARIES};${GTEST_MAIN_LIBRARIES})
ENDIF()

SET(GTEST_FOUND          ${GTEST_FOUND}          PARENT_SCOPE)
SET(GTEST_INCLUDE_DIRS   ${GTEST_INCLUDE_DIRS}   PARENT_SCOPE)
SET(GTEST_LIBRARIES      ${GTEST_LIBRARIES}      PARENT_SCOPE)
SET(GTEST_MAIN_LIBRARIES ${GTEST_MAIN_LIBRARIES} PARENT_SCOPE)
SET(GTEST_BOTH_LIBRARIES ${GTEST_BOTH_LIBRARIES} PARENT_SCOPE)
