#pragma once

#define GLFW_INCLUDE_GLU

#if __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif

#if __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"
#endif

#include <GLFW/glfw3.h>

#if __GNUC__
#pragma GCC diagnostic pop
#endif

#if __clang__
#pragma clang diagnostic pop
#endif
