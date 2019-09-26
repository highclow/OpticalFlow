#include <cstdio>
#include "gtest/gtest.h"

using ::testing::InitGoogleTest;

GTEST_API_ int main(int argc, char **argv) {
  printf("Running main() from %s\n", __FILE__);
  InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
