#include <gtest/gtest.h>

extern "C" {
    #include "../include/cli.h"
}

TEST(CliTest, NoArguments)
{
    const char* path = parse_args(1, NULL);\

    ASSERT_STREQ(path, NULL);
}

TEST(CliTest, SmallSampleFile)
{
    char* argv[] = {"foo", "-s"};

    const char *path = parse_args(2, argv);

    ASSERT_STREQ(path, "small-sample.txt");
}

TEST(CliTest, LargeSampleFile)
{
    char* argv[] = {"foo", "-l"};

    const char* path = parse_args(2, argv);
    
    ASSERT_STREQ(path, "large-sample.txt");
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}