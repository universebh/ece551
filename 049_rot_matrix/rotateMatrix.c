//Code starts

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LDIM 10
#define CDIM 10

void printMatrix(char matrix[][CDIM]) {
  for (int i = 0; i < LDIM; i++) {
    for (int j = 0; j < CDIM; j++) {
      printf("%c", matrix[i][j]);
      //if (j < CDIM - 1) {
      //  printf(" ");
      // }
    }
    printf("\n");
  }
}

void rotateMatrix(char matrix[][CDIM]) {
  char matrixRotated[LDIM][CDIM];
  for (int i = 0; i < LDIM; i++) {
    for (int j = 0; j < CDIM; j++) {
      matrixRotated[j][CDIM - 1 - i] = matrix[i][j];
    }
  }
  for (int i = 0; i < LDIM; i++) {
    for (int j = 0; j < CDIM; j++) {
      matrix[i][j] = matrixRotated[i][j];
    }
  }
}

void closeFile(FILE * f) {
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    exit(EXIT_FAILURE);
  }
}

void readLines_(FILE * f, char * line, char matrix[][CDIM]) {
  int lineIndex = 0;
  while (fgets(line, 2 * CDIM, f) != NULL) {
    if (lineIndex >= 2 * LDIM) {
      break;
    }
    if (strchr(line, '\n') == NULL) {
      fprintf(stderr, "Line is too long\n");
      exit(EXIT_FAILURE);
    }
    if (strlen(line) - 1 != CDIM) {
      fprintf(stderr, "Column number (%lu) does not match\n", strlen(line) - 1);
      exit(EXIT_FAILURE);
    }
    for (int j = 0; j < CDIM; j++) {
      matrix[lineIndex][j] = line[j];
    }
    lineIndex++;
  }
  if (lineIndex != LDIM) {
    fprintf(stderr, "Line number (%d) does not match\n", lineIndex);
    exit(EXIT_FAILURE);
  }
}

void main_(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: rotateMatrix inputFileName\n");
    exit(EXIT_FAILURE);
  }
  FILE * f = NULL;
  if ((f = fopen(argv[1], "r")) == NULL) {
    perror("Could not open file");
    exit(EXIT_FAILURE);
  }
  char line[2 * CDIM];
  char matrix[2 * LDIM][CDIM];
  readLines_(f, line, matrix);
  rotateMatrix(matrix);
  printMatrix(matrix);
}

int main(int argc, char ** argv) {
  main_(argc, argv);
  return EXIT_SUCCESS;
}

//Code ends
