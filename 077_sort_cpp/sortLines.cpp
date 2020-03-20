#include <algorithm>
#include <cerrno>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> & readFile(std::vector<std::string> & strArr) {
  while (!std::cin.eof()) {
    std::string str;
    //std::cin >> str;
    //if (str.size() == 0) {
    //  str = "";
    //}
    getline(std::cin, str);
    strArr.push_back(str);
  }
  strArr.erase(strArr.end());
  return strArr;
}

std::vector<std::string> & readFile(std::vector<std::string> & strArr, std::ifstream & in) {
  while (!in.eof()) {
    std::string str;
    getline(in, str);
    strArr.push_back(str);
  }
  strArr.erase(strArr.end());
  return strArr;
}

void printStrArr(const std::vector<std::string> & strArr) {
  std::vector<std::string>::const_iterator it = strArr.begin();
  while (it != strArr.end()) {
    std::cout << *it << std::endl;
    ++it;
  }
}

void sortStrArr(std::vector<std::string> & strArr) {
  if (strArr.size() > 0) {
    std::sort(strArr.begin(), strArr.end());
  }
}

int main(int argc, char ** argv) {
  if (argc < 2) {
    std::vector<std::string> strArr;
    readFile(strArr);
    if (strArr.size() < 1) {
      std::cerr << "no input received" << std::endl;
      return EXIT_FAILURE;
    }
    sortStrArr(strArr);
    printStrArr(strArr);
  }
  for (int i = 1; i < argc; i++) {
    std::vector<std::string> strArr;
    std::ifstream fin;
    fin.open(argv[i]);
    if (!fin) {
      std::cerr << "open failure" << std::endl;
      perror("error");
      return EXIT_FAILURE;
    }
    readFile(strArr, fin);
    if (strArr.size() < 1) {
      std::cerr << "no input received" << std::endl;
      fin.close();
      return EXIT_FAILURE;
    }
    sortStrArr(strArr);
    printStrArr(strArr);
    fin.close();
  }
  return EXIT_SUCCESS;
}
