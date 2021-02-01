#include <iomanip>
#include <iostream>

#define BEGIN_TEST(TestSuite, TestName)                                    \
   bool test__##TestSuite##__##TestName(void)                              \
{                                                                          \
      bool isTrue{true};

#define END_TEST                                                           \
   return isTrue;                                                          \
}

#define EXPECT_EQ(arg1, arg2) isTrue &= (arg1 == arg2);

#define RUN_TEST(TestSuite, TestName)                                      \
{                                                                          \
   bool ret = test__##TestSuite##__##TestName();                           \
   std::cout << std::left << std::setfill('-')                             \
   << std::setw(50) << #TestSuite " --> " #TestName " ";                   \
                                                                           \
   if(ret)                                                                 \
   {                                                                       \
      std::cout << std::setw(10)                                           \
      << std::left << "\x1b[38;5;40m   OK \x1b[0m" /* colored in Green*/   \
      << std::endl;                                                        \
   }                                                                       \
   else                                                                    \ 
   {                                                                       \
      std::cout << std::setw(10)                                           \
      << std::left << "\x1b[38;5;160m   FAILED \x1b[0m" /* colored in Red*/\
      << std::endl;                                                        \
   }                                                                       \
} /* Coloring valid for *nix systems. */