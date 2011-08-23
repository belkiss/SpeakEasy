#include <iostream>
#include <cassert>
#include "SE_Types.h"

int main()
{
    F32 float32 = 0.f;
    std::cout << "F32 float32 size : " << sizeof(float32) * 8 << std::endl;
    assert(sizeof(float32) == 4);

    U8 uint8 = 0;
    std::cout << "U8 uint8 size : " << sizeof(uint8) * 8 << std::endl;
    assert(sizeof(uint8) == 1);

    I8 int8 = 0;
    std::cout << "I8 int8 size : " << sizeof(int8) * 8 << std::endl;
    assert(sizeof(int8) == 1);

    U16 uint16 = 0;
    std::cout << "U16 uint16 size : " << sizeof(uint16) * 8 << std::endl;
    assert(sizeof(uint16) == 2);

    I16 int16 = 0;
    std::cout << "I16 int16 size : " << sizeof(int16) * 8 << std::endl;
    assert(sizeof(int16) == 2);

    U32 uint32 = 0;
    std::cout << "U32 uint32 size : " << sizeof(uint32) * 8 << std::endl;
    assert(sizeof(uint32) == 4);

    I32 int32 = 0;
    std::cout << "I32 int32 size : " << sizeof(int32) * 8 << std::endl;
    assert(sizeof(int32) == 4);

    U64 uint64 = 0;
    std::cout << "U64 uint64 size : " << sizeof(uint64) * 8 << std::endl;
    assert(sizeof(uint64) == 8);

    I64 int64 = 0;
    std::cout << "I64 int64 size : " << sizeof(int64) * 8 << std::endl;
    assert(sizeof(int64) == 8);
}