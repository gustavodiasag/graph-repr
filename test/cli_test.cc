/**
 * Copyright (c) 2023 Gustavo Dias de Aguiar

 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <gtest/gtest.h>

namespace {

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

    ASSERT_STREQ(path, "../small-sample.txt");
}

TEST(CliTest, LargeSampleFile)
{
    char* argv[] = {"foo", "-l"};

    const char* path = parse_args(2, argv);
    
    ASSERT_STREQ(path, "../large-sample.txt");
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

}
