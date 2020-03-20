#include "kv.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define BUFFER_SIZE 1024

void stripNewline(char * str) {
  char * p = strchr(str, '\n');
  if (p != NULL) {
    *p = '\0';
  }
}

char ** readLines(FILE * f) {
  char ** lines = NULL;
  char * curr = NULL;
  size_t sz = 0;
  size_t i = 0;
  bool isEmpty = true;
  while (getline(&curr, &sz, f) >= 0) {
    if (isEmpty) {
      isEmpty = false;
    }
    lines = realloc(lines, (i + 1) * sizeof(*lines));
    lines[i] = curr;
    curr = NULL;
    i++;
  }
  if (isEmpty) {
    fprintf(stderr, "Empty file\n");
    if (curr != NULL) {
      free(curr);
      curr = NULL;
    }
    //assert(fclose(f) == 0);
    //exit(EXIT_FAILURE);
    return NULL;
  }
  if (curr != NULL) {
    free(curr);
    curr = NULL;
  }
  lines = realloc(lines, (i + 1) * sizeof(*lines));
  lines[i] = NULL;
  return lines;
}

void freeLines(char ** lines) {
  size_t i = 0;
  if (lines != NULL) {
    while (lines[i] != NULL) {
      free(lines[i]);
      lines[i] = NULL;
      i++;
    }
    free(lines);
    lines = NULL;
  }
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    perror("Cannot open current file");
    fprintf(stderr, "Fail to open %s\n", fname);
    exit(EXIT_FAILURE);
  }
  char ** lines = readLines(f);
  if (lines == NULL) {  //empty file
    assert(fclose(f) == 0);
    return NULL;
  }
  kvarray_t * kvArr = malloc(sizeof(*kvArr));
  kvArr->array = NULL;
  kvArr->length = 0;
  size_t i = 0;
  while (lines[i] != NULL) {
    char * delim = "=";
    char * ptk = NULL;
    char * psv = NULL;
    ptk = strtok_r(lines[i], delim, &psv);
    if (strlen(psv) == 0) {
      //fprintf(stderr, "Fail to interpret %s\n", lines[i]);
      i++;
      continue;
    }

    kvpair_t * kv = malloc(sizeof(*kv));
    //kv->key = malloc(BUFFER_SIZE * sizeof(*kv->key));
    //kv->value = malloc(BUFFER_SIZE * sizeof(*kv->value));
    kv->key = malloc((strlen(ptk) + 1) * sizeof(*kv->key));
    kv->value = malloc((strlen(psv) + 1) * sizeof(*kv->value));
    strcpy(kv->key, ptk);
    strcpy(kv->value, psv);
    stripNewline(kv->value);
    kvArr->array = realloc(kvArr->array, (kvArr->length + 1) * sizeof(*kvArr->array));
    kvArr->array[kvArr->length] = kv;
    kvArr->length++;
    i++;
  }
  freeLines(lines);
  assert(fclose(f) == 0);
  return kvArr;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  if (pairs != NULL) {
    if (pairs->array != NULL) {
      for (size_t i = 0; i < pairs->length; i++) {
        if (pairs->array[i] != NULL) {
          if (pairs->array[i]->key != NULL) {
            free(pairs->array[i]->key);
            pairs->array[i]->key = NULL;
          }
          if (pairs->array[i]->value != NULL) {
            free(pairs->array[i]->value);
            pairs->array[i]->value = NULL;
          }
          free(pairs->array[i]);
          pairs->array[i] = NULL;
        }
      }
      free(pairs->array);
      pairs->array = NULL;
    }
    free(pairs);
    pairs = NULL;
  }
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  if (pairs == NULL) {
    return;
  }
  for (size_t i = 0; i < pairs->length; i++) {
    printf("key = '%s' value = '%s'\n", pairs->array[i]->key, pairs->array[i]->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  if (pairs == NULL) {
    return NULL;
  }
  for (size_t i = 0; i < pairs->length; i++) {
    if (strcmp(key, pairs->array[i]->key) == 0) {
      return pairs->array[i]->value;
    }
  }
  return NULL;
}
