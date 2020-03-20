#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_TESTS 12
int main(void) {
  //char * testData[NUM_TESTS] = {"apple", "banana", NULL,"apple",
  //				"frog","sword","bear",NULL,
  //				"frog","apple", "zebra", "knight"};
  //char * testData[NUM_TESTS];
  //for (int i = 0; i < NUM_TESTS; i++) {
  //testData[i] = NULL;
  //}
  char * testData[NUM_TESTS] = {"",
                                "banana",
                                NULL,
                                "apple",
                                "frog",
                                "sword",
                                "bear",
                                NULL,
                                "frog",
                                "apple",
                                "zebra",
                                "knight"};

  counts_t * testCounts = createCounts();
  for (int i = 0; i < NUM_TESTS; i++) {
    addCount(testCounts, testData[i]);
  }
  printCounts(testCounts, stdout);
  freeCounts(testCounts);
  return EXIT_SUCCESS;
}
