#include "counts.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FIRST -1
//#define BUFFER_SIZE 1024

counts_t * createCounts(void) {
  //WRITE ME
  counts_t * counts = malloc(sizeof(*counts));
  counts->countArr = NULL;
  counts->length = 0;
  return counts;
}

int increStrat(counts_t * c, const char * name) {
  if (c->length == 0) {
    return FIRST;
  }
  for (size_t i = 0; i < c->length; i++) {
    if (c->countArr[i]->string == NULL || name == NULL) {
      if (c->countArr[i]->string == NULL && name == NULL) {
        return i;
      }
    }
    else if (strcmp(c->countArr[i]->string, name) == 0) {
      return i;
    }
  }
  return FIRST;
}

void createOneCount(counts_t * c) {
  c->countArr = realloc(c->countArr, (c->length + 1) * sizeof(*c->countArr));
  c->countArr[c->length] = malloc(sizeof(*c->countArr[c->length]));
  c->countArr[c->length]->string = NULL;
  c->countArr[c->length]->times = 0;
}

void addCount(counts_t * c, const char * name) {
  //WRITE ME
  assert(c != NULL);
  int idx;
  if ((idx = increStrat(c, name)) == FIRST) {
    createOneCount(c);
    if (name != NULL) {
      // c->countArr[c->length]->string =
      //    malloc(BUFFER_SIZE * sizeof(*c->countArr[c->length]->string));
      c->countArr[c->length]->string =
          malloc((strlen(name) + 1) * sizeof(*c->countArr[c->length]->string));
      strcpy(c->countArr[c->length]->string, name);
    }
    c->countArr[c->length]->times++;
    c->length++;
  }
  else {
    c->countArr[idx]->times++;
  }
}

void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  int hasUnk = 0;
  size_t unkIdx = 0;
  for (size_t i = 0; i < c->length; i++) {
    if (c->countArr[i]->string == NULL) {
      hasUnk = 1;
      unkIdx = i;
    }
    else {
      fprintf(outFile, "%s: %zu\n", c->countArr[i]->string, c->countArr[i]->times);
    }
  }
  if (hasUnk) {
    fprintf(outFile, "<unknown>: %zu\n", c->countArr[unkIdx]->times);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  if (c != NULL) {
    if (c->countArr != NULL) {
      for (size_t i = 0; i < c->length; i++) {
        if (c->countArr[i] != NULL) {
          if (c->countArr[i]->string != NULL) {
            free(c->countArr[i]->string);
            c->countArr[i]->string = NULL;
          }
          free(c->countArr[i]);
          c->countArr[i] = NULL;
        }
      }
      free(c->countArr);
      c->countArr = NULL;
    }
    free(c);
    c = NULL;
  }
}
