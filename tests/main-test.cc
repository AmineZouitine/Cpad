#include <gtest/gtest.h>

#include "init-tests.hh"


int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}