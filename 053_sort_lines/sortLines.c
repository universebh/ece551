#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

void printResults_(char ** lines) {
  size_t i = 0;
  while (lines[i] != NULL) {
    fprintf(stdout, "%s", lines[i]);
    free(lines[i]);
    i++;
  }
  //free(lines[i]); we do not need to free NULL
}

char ** readInput_(FILE * f) {
  char ** lines = NULL;
  char * curr = NULL;
  size_t sz = 0;    //init not needed
  ssize_t len = 0;  //init not needed
  size_t i = 0;
  bool isVoidInput = true;
  while ((len = getline(&curr, &sz, f)) >= 0) {
    isVoidInput = false;
    lines = realloc(lines, (i + 1) * sizeof(*lines));
    lines[i] = curr;
    curr = NULL;
    i++;
  }
  if (curr != NULL) {
    free(curr);
  }
  if (isVoidInput) {
    fprintf(stderr, "No input received\n");
    if (fclose(f) == -1) {
      fprintf(stderr, "Failed in closing file (in readInput_)\n");
      exit(EXIT_FAILURE);
    }
    exit(EXIT_FAILURE);
  }
  //free of allocated blocks pointed by lines waiting
  lines = realloc(lines, (i + 1) * sizeof(*lines));
  lines[i] = NULL;
  //return i;  //return line numbers excluding NULL
  return lines;
}

size_t getLineLength_(char ** lines) {
  char ** pls = lines;
  size_t lineLength = 0;
  while (*pls != NULL) {
    lineLength++;
    pls++;
  }
  return lineLength;
}

void main_(int argc, char ** argv) {
  if (argc < 2) {
    //read from standard input
    //sort the lines of input
    //print the rusults
    //free allocate memories
    char ** lines = readInput_(stdin);
    size_t len = getLineLength_(lines);
    sortData(lines, len);
    printResults_(lines);
    free(lines);
  }
  else {
    //treat each argument as an input file name
    //open each file
    //read all of line of data in it
    //sort the lines
    //print the results
    //free allocate memories
    FILE * fv[argc];  //place NULL to its last element
    for (int i = 0; i < argc - 1; i++) {
      fv[i] = fopen(argv[i + 1], "r");
      if (fv[i] == NULL) {
        fprintf(stderr, "Failed in opening file (%s)\n", argv[i]);
        exit(EXIT_FAILURE);
      }
      char ** lines = readInput_(fv[i]);
      size_t len = getLineLength_(lines);
      sortData(lines, len);
      printResults_(lines);
      free(lines);
      if (fclose(fv[i]) == -1) {
        fprintf(stderr, "Failed in closing file (%s)\n", argv[i]);
        exit(EXIT_FAILURE);
      }
    }
    fv[argc - 1] = NULL;
  }
}

int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  main_(argc, argv);
  return EXIT_SUCCESS;
}
