#include "misc.h"

#include <cassert>
#include <cmath>
#include <fstream>
#include <sstream>

#include "config.h"


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
float se_misc::toRad( const float inDeg )
{
    return (float)M_PI*inDeg/180.f;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void se_misc::loadFileToString( const std::string & inFileName,
                                      std::string & outFileSource)
{
    ////////////////////////////////////////////////////////////////////////////
    std::ifstream fileStream(inFileName.c_str(), std::ios::binary);
    if (!fileStream.good())
    {
        assert(false);// File does not exist
    }

    //This line reads in the whole file into a string
    outFileSource = std::string( std::istreambuf_iterator<char>(fileStream),
                                (std::istreambuf_iterator<char>()));

    fileStream.close();
    ////////////////////////////////////////////////////////////////////////////
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void se_misc::computeW( Eigen::Quaternionf & ioQuat )
{
    float tmp = 1.f - (ioQuat.x() * ioQuat.x())
                    - (ioQuat.y() * ioQuat.y())
                    - (ioQuat.z() * ioQuat.z());

    ioQuat.w() = tmp < 0 ? 0.f : sqrt(tmp);
}
