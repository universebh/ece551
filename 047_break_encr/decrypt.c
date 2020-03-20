//Code starts

#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define NO_ALPHA_LETTERS -99
#define INVALID_KEY_OBTAINED -98

void closeFile(FILE * f) {
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    exit(EXIT_FAILURE);
  }
}

int getLargestIndex(int * array, int nNum) {
  assert(nNum > 0);
  int largestIndex = 0;
  for (int i = 1; i < nNum; i++) {
    if (array[largestIndex] < array[i]) {
      largestIndex = i;
    }
  }
  return largestIndex;
}

int decrypt_helper_(FILE * f) {
  int count[26] = {0};
  int nCount = 26;
  int chr;
  bool noAlphaLetters = true;
  while ((chr = fgetc(f)) != EOF) {
    if (isalpha(chr)) {
      chr = tolower(chr);
      if (noAlphaLetters == true) {
        noAlphaLetters = false;
      }
      chr = tolower(chr);
      count[chr - 'a']++;
    }
  }
  if (noAlphaLetters == true) {
    return NO_ALPHA_LETTERS;
  }
  int key = (getLargestIndex(count, nCount) - ('e' - 'a') + 26) % 26;
  if (!(key >= 0 && key < 26)) {
    return INVALID_KEY_OBTAINED;
  }
  return key;
}

void decrypt(const char * fileName) {
  FILE * f = fopen(fileName, "r");
  if (f == NULL) {
    perror("Could not open file");
    exit(EXIT_FAILURE);
  }
  int key = decrypt_helper_(f);
  if (key == NO_ALPHA_LETTERS) {
    fprintf(stderr, "Decrypt: No alphabet letters in the file\n");
    closeFile(f);
    exit(EXIT_FAILURE);
  }
  else if (key == INVALID_KEY_OBTAINED) {
    fprintf(stderr, "Decrypt: Invalid Key was obtained\n");
    closeFile(f);
    exit(EXIT_FAILURE);
  }
  else {
    fprintf(stdout, "%d\n", key);
  }
  closeFile(f);
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: decrypt inputFileName\n");
    return EXIT_FAILURE;
  }
  decrypt(argv[1]);
  return EXIT_SUCCESS;
}

//Code ends
