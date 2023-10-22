#include <gtest/gtest.h>

extern "C" {
    #include "../include/list.h"
}

TEST(ListTest, ListInitialization)
{
    List* l = (List*)malloc(sizeof(List));
    list_init(l, sizeof(void*), NULL);

    ASSERT_EQ(list_size(l), 0);
    ASSERT_EQ(list_dsize(l), 8);
}

TEST(ListTest, ListInsertion)
{
    List* l = (List*)malloc(sizeof(List));
    list_init(l, sizeof(int), NULL);

    int i = 10;
    list_ins_next(l, NULL, &i);

    ASSERT_EQ(*(int*)list_head(l), 10);
}