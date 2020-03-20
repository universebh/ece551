#include <dirent.h>
#include <limits.h>
#include <sys/types.h>

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <typeinfo>
#include <unordered_map>
#include <vector>

#define BUFFER_SIZE 256

using std::cerr;
using std::cout;
using std::endl;

typedef struct dirent dirent_t;

std::string & readFile(std::string & content, std::ifstream & in) {
  content = "";
  while (!in.eof()) {
    std::string str;
    getline(in, str);
    content = content + str + "\n";
  }
  //size()-1 is correct
  content = content.substr(0, content.size() - 1);
  return content;
}

void fileManip(const char * path, std::unordered_multimap<std::string, std::string> & hashMap) {
  std::string content = "";
  std::ifstream fin;
  fin.open(path);
  if (!fin) {
    std::stringstream ss;
    ss << "open failure: " << path;
    cerr << ss.str() << endl;
    throw std::exception();
  }
  readFile(content, fin);
  //cout << "reading from: " << path << endl;
  //cout << content << endl;
  //cout << "---------" << endl;
  char * fullPath = NULL;
  fullPath = realpath(path, NULL);
  std::stringstream ss;
  ss << fullPath;
  std::pair<std::string, std::string> keyval(content, ss.str());
  if (fullPath != NULL) {
    free(fullPath);
    fullPath = NULL;
  }
  hashMap.insert(keyval);
  fin.close();
}

bool isPrime(unsigned long n) {
  bool ans = true;
  for (unsigned long i = 2; i <= n / 2; i++) {
    if (n % i == 0) {
      ans = false;
      break;
    }
  }
  return ans;
}

unsigned long cptHashBucketLen(unsigned long n) {
  while (!isPrime(n)) {
    n++;
  }
  return n;
}

void goNext(const char * curr, const char * object, char * next) {
  strcpy(next, curr);
  strcat(next, "/");
  strcat(next, object);
}

void readDir(char * arg,
             unsigned long & n,
             std::unordered_multimap<std::string, std::string> & hashMap,
             bool store) {
  DIR * dir;
  dirent_t * ent;
  if ((dir = opendir(arg)) != NULL) {
    while ((ent = readdir(dir)) != NULL) {
      if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0) {
        char next[BUFFER_SIZE];
        if (ent->d_type == DT_DIR) {
          goNext(arg, ent->d_name, next);
          readDir(next, n, hashMap, store);
        }
        else {
          if (store) {
            goNext(arg, ent->d_name, next);
            fileManip(next, hashMap);
          }
          //else {
          //  goNext(arg, ent->d_name, next);
          //  char * fullPath = NULL;
          //  fullPath = realpath(next, NULL);
          //  cout << fullPath << endl;
          //  if (fullPath != NULL) {
          //    free(fullPath);
          //    fullPath = NULL;
          //  }
          //}
          n++;
        }
      }
    }
    closedir(dir);
  }
  else {
    std::stringstream ss;
    ss << "incorrect directory: " << arg;
    cerr << ss.str() << endl;
    throw std::exception();
  }
}

unsigned long readDir(char * arg,
                      std::unordered_multimap<std::string, std::string> & hashMap,
                      bool store = false) {
  unsigned long n = 0;
  readDir(arg, n, hashMap, store);
  return n;
}

unsigned long hash(const std::vector<std::string> & strArr) {
  cout << strArr[0] << endl;
  return 0;
}

int main(int argc, char ** argv) {
  if (argc < 2) {
    std::stringstream ss;
    ss << "usage: ./dedup dir";
    cerr << ss.str() << endl;
    throw std::exception();
  }
  std::unordered_multimap<std::string, std::string> hashMap;
  for (int i = 1; i < argc; i++) {
    readDir(argv[i], hashMap, true);
  }
  //unsigned long n = readDir(argv[i], hashMap, true);
  //unsigned long r = 0;
  //unsigned long p = 0;
  cout << "#!/bin/bash" << endl;
  for (std::unordered_multimap<std::string, std::string>::iterator x = hashMap.begin();
       x != hashMap.end();
       ++x) {
    int c = hashMap.count((*x).first);
    if (c > 1) {
      auto range = hashMap.equal_range((*x).first);
      std::string retain;
      for (std::unordered_multimap<std::string, std::string>::iterator it = range.first;
           it != range.second;
           ++it) {
        if (it == range.first) {
          retain = (*it).second;
        }
        else {
          cout << "#Removing " << (*it).second;
          cout << " (duplicate of " << retain << ")." << endl;
          cout << "rm " << (*it).second << endl;
        }
      }
      //p++;
      for (int j = 0; j < c - 1; j++) {
        ++x;
      }
      //r++;
    }
  }
  //cout << "hash size: " << hashMap.size() << endl;
  //cout << "file number: " << n << endl;
  //cout << "repeat group: " << r << endl;
  //cout << "printed group: " << p << endl;
  return (EXIT_SUCCESS);
}
