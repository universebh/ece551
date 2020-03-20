#ifndef _IL_H_
#define _IL_H_

#include <cstdlib>

void testList(void);

class IntList
{
 private:
  class Node
  {
   public:
    int data;
    Node * next;
    Node * prev;
    Node() : data(0), next(NULL), prev(NULL){};
  };
  Node * head;
  Node * tail;
  int size;

 public:
  IntList();
  IntList(const IntList & rhs);
  IntList & operator=(const IntList & rhs);
  ~IntList();
  void addFront(const int & item);
  void addBack(const int & item);
  bool remove(const int & item);
  int & operator[](int index);
  const int & operator[](int index) const;
  int find(const int & item);
  int getSize() const;
  friend void testList(void);
  friend void testPtr(const IntList & lst);
  friend void testVal(const IntList & lst, int val[]);
  friend void testCstr(void);
  friend void testCpCstr(void);
  friend void testAsmOp(void);
  friend void testAdds(void);
  friend void testRm(void);
  friend void testIdxOp(void);
  friend void testCstIdxOp(void);
  friend void testFind(void);
  friend void testGetSz(void);
};

void testPtr(const IntList & lst);
void testVal(const IntList & lst, int val[]);
void testCstr(void);
void testCpCstr(void);
void testAsmOp(void);
void testAdds(void);
void testRm(void);
void testIdxOp(void);
void testCstIdxOp(void);
void testFind(void);
void testGetSz(void);

#endif
