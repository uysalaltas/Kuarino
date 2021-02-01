#include "test.hpp"
#include "../utils.cpp"
#include "../utils.h"

using namespace std;

utils util_test;

char arr1[3];
char arr2[12];
char arr3[4];

BEGIN_TEST(G_Control, T1)
{
  util_test.initialize_char_array(3, arr1);
  util_test.initialize_char_array(12, arr2);
  util_test.initialize_char_array(4, arr3);

  char msg[22] = {'9','G','1', 10,'X','1',32,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

  char arr1_comp[3] = {'G','1', 0};
  char arr2_comp[12] = {'X','1',0,0,0,0,0,0,0,0,0,0};
  char arr3_comp[4] = {0,0,0,0};

  util_test.split_gcode(arr1, arr2, arr3, msg);

  for (int i = 0; i < 3; i++)
  {
    EXPECT_EQ(arr1_comp[i], arr1[i])
  }

  for (int i = 0; i < 12; i++)
  {
    EXPECT_EQ(arr2[i], arr2_comp[i])
  }

  for (int i = 0; i < 4; i++)
  {
    EXPECT_EQ(arr3_comp[i], arr3[i])
  }

}END_TEST

BEGIN_TEST(G_Control, T2)
{
  util_test.initialize_char_array(3, arr1);
  util_test.initialize_char_array(12, arr2);
  util_test.initialize_char_array(4, arr3);

  char msg[22] = {'9','G','1', 10,'X','1','Y','1',32,0,0,0,0,0,0,0,0,0,0,0,0,0};

  char arr1_comp[3] = {'G','1', 0};
  char arr2_comp[12] = {'X','1','Y','1',0,0,0,0,0,0,0,0};
  char arr3_comp[4] = {0,0,0,0};

  util_test.split_gcode(arr1, arr2, arr3, msg);

  for (int i = 0; i < 3; i++)
  {
    EXPECT_EQ(arr1_comp[i], arr1[i])
  }

  for (int i = 0; i < 12; i++)
  {
    EXPECT_EQ(arr2[i], arr2_comp[i])
  }

  for (int i = 0; i < 4; i++)
  {
    EXPECT_EQ(arr3_comp[i], arr3[i])
  }

}END_TEST

BEGIN_TEST(G_Control, T3)
{
  util_test.initialize_char_array(3, arr1);
  util_test.initialize_char_array(12, arr2);
  util_test.initialize_char_array(4, arr3);

  char msg[22] = {'9','G','1', 10,'X','1','0','Y','1','0',32,0,0,0,0,0,0,0,0,0,0,0};

  char arr1_comp[3] = {'G','1', 0};
  char arr2_comp[12] = {'X','1','0','Y','1','0',0,0,0,0,0,0};
  char arr3_comp[4] = {0,0,0,0};

  util_test.split_gcode(arr1, arr2, arr3, msg);

  for (int i = 0; i < 3; i++)
  {
    EXPECT_EQ(arr1_comp[i], arr1[i])
  }

  for (int i = 0; i < 12; i++)
  {
    EXPECT_EQ(arr2[i], arr2_comp[i])
  }

  for (int i = 0; i < 4; i++)
  {
    EXPECT_EQ(arr3_comp[i], arr3[i])
  }

}END_TEST

int main()
{
  RUN_TEST(G_Control, T1)
  RUN_TEST(G_Control, T2)
  RUN_TEST(G_Control, T3)
  return 0;
}