#include <iostream>
#include "SE_Types.h"

I32 main()
{
    static_assert(sizeof(F32) == 4,
                  "sizeof(float32) != 4 on this machine");

    static_assert(sizeof(U8) == 1,
                  "sizeof(U8) != 1 on this machine");

    static_assert(sizeof(I8) == 1,
                  "sizeof(I8) != 1 on this machine");

    static_assert(sizeof(U16) == 2,
                  "sizeof(U16) != 2 on this machine");

    static_assert(sizeof(I16) == 2,
                  "sizeof(I16) != 2 on this machine");

    static_assert(sizeof(U32) == 4,
                  "sizeof(U32) != 4 on this machine");

    static_assert(sizeof(I32) == 4,
                  "sizeof(I32) != 4 on this machine");

    static_assert(sizeof(U64) == 8,
                  "sizeof(U64) != 8 on this machine");

    static_assert(sizeof(I64) == 8,
                  "sizeof(I64) != 8 on this machine");

    return EXIT_SUCCESS;
}

