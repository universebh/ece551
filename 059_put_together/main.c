#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

//#define BUFFER_SIZE 1024

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  FILE * f = fopen(filename, "r");
  assert(f != NULL);
  char ** keys = NULL;
  keys = readLines(f);
  if (keys != NULL) {
    char * currValue = NULL;
    //char valstr[BUFFER_SIZE];
    counts_t * counts = createCounts();
    size_t j = 0;
    while (keys[j] != NULL) {
      stripNewline(keys[j]);
      char * pcv = lookupValue(kvPairs, keys[j]);
      //if (pcv == NULL) {
      //currValue = pcv;
      //}
      //else {
      //strcpy(valstr, pcv);
      //currValue = valstr;
      //}
      currValue = pcv;
      addCount(counts, currValue);
      currValue = NULL;
      j++;
    }
    freeLines(keys);
    assert(fclose(f) == 0);
    return counts;
  }
  assert(fclose(f) == 0);
  return NULL;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  if (argc <= 2) {
    fprintf(stderr, "./main kv.txt list.txt ...\n");
    return EXIT_FAILURE;
  }
  kvarray_t * kv = readKVs(argv[1]);
  //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * c = NULL;
    c = countFile(argv[i], kv);
    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);
    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w");
    assert(f != NULL);
    //print the counts from c into the FILE f
    printCounts(c, f);
    //close f
    assert(fclose(f) == 0);
    //free the memory for outName and c
    if (outName != NULL) {
      free(outName);
      outName = NULL;
    }
    if (c != NULL) {
      freeCounts(c);
      c = NULL;
    }
  }
  //free the memory for kv
  freeKVs(kv);
  return EXIT_SUCCESS;
}
