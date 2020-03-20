#include "readFreq.h"

#include <stdio.h>

#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>

void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  //WRITE ME!
  std::ifstream fin;
  fin.open(fname);
  if (!fin) {
    std::stringstream ss;
    ss << "open failure: " << fname;
    cerr << ss.str() << endl;
    throw std::exception();
  }
  uint64_t * ans = new uint64_t[257]();
  int c;
  while ((c = fin.get()) != EOF) {
    ans[int(c)]++;
  }
  ans[256]++;
  fin.close();
  return ans;
}
