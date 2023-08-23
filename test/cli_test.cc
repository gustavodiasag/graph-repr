#include <gtest/gtest.h>
#include "../include/cli.h"

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}