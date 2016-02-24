/*
 * PeakTestsMain.cpp
 *
 *  Created on: 20.02.2016
 *      Author: philgras
 */


#include <stdio.h>

#include "gtest/gtest.h"

GTEST_API_ int main(int argc, char **argv) {
  printf("Run peak tests...\n");
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

