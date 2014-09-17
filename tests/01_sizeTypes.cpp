#include "SE_Types.h"
#include "gtest/gtest.h"

TEST(BaseTypes, SizeTest)
{
    ASSERT_EQ(4, sizeof(F32)) << "sizeof(F32) != 4 on this machine";
    ASSERT_EQ(1, sizeof(U8))  << "sizeof(U8)  != 1 on this machine";
    ASSERT_EQ(1, sizeof(I8))  << "sizeof(I8)  != 1 on this machine";
    ASSERT_EQ(2, sizeof(U16)) << "sizeof(U16) != 2 on this machine";
    ASSERT_EQ(2, sizeof(I16)) << "sizeof(I16) != 2 on this machine";
    ASSERT_EQ(4, sizeof(U32)) << "sizeof(U32) != 4 on this machine";
    ASSERT_EQ(4, sizeof(I32)) << "sizeof(I32) != 4 on this machine";
    ASSERT_EQ(8, sizeof(U64)) << "sizeof(U64) != 8 on this machine";
    ASSERT_EQ(8, sizeof(I64)) << "sizeof(I64) != 8 on this machine";
}
