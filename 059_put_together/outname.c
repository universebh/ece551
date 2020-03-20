#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  size_t len = 0;  //length of str without terminate sign
  const char * pnm = inputName;
  while (*pnm != '\0') {
    len++;
    pnm++;
  }
  pnm = NULL;
  char * outputName = malloc((len + 8) * sizeof(*outputName));
  strcpy(outputName, inputName);
  strcat(outputName, ".counts");
  return outputName;
}
