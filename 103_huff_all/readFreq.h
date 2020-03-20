#ifndef __READ_FREQ_H__
#define __READ_FREQ_H__
#include <assert.h>
#include <stdint.h>

#include <iostream>

using std::cerr;
using std::cout;
using std::endl;

uint64_t * readFrequencies(const char * fname);
void printSym(std::ostream & s, unsigned sym);
#endif
