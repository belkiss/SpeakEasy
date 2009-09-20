#pragma once
#include <glibmm.h>
#include <string>

float toRad( const float inDeg );

void loadFileToString( const Glib::ustring & inFileName,
                             Glib::ustring & outFileSource);
