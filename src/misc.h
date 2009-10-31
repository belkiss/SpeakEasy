#pragma once
#include <glibmm.h>
#include <string>

#include <Eigen/Geometry>

namespace se_misc
{
    float toRad( const float inDeg );

    void  loadFileToString( const Glib::ustring & inFileName,
                                  Glib::ustring & outFileSource);

    void  computeW( Eigen::Quaternionf & ioQuat );
}
