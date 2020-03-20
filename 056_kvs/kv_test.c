#include "kv.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_LOOKUPS 5
int main(int argc, char ** argv) {
  kvarray_t * array = NULL;
  if (argc > 1) {
    assert(argc < 3);
    array = readKVs(argv[1]);
  }
  else {
    array = readKVs("test.txt");
  }
  printf("Printing all keys\n\n");
  printKVs(array);
  char * tests[NUM_LOOKUPS] = {"banana", "grapes", "cantaloupe", "lettuce", "orange"};
  for (int i = 0; i < NUM_LOOKUPS; i++) {
    printf("lookupValue('%s')=%s\n", tests[i], lookupValue(array, tests[i]));
  }
  freeKVs(array);
  return EXIT_SUCCESS;
}
