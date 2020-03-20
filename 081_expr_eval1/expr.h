#ifndef __EXPR_H__
#define __EXPR_H__

#include <iostream>
#include <sstream>
#include <string>

class Expression
{
 public:
  virtual ~Expression() {}
  virtual std::string toString() const = 0;
};

class NumExpression : public Expression
{
 private:
  long num;

 public:
  NumExpression(long num_) : num(num_) {}
  virtual std::string toString() const {
    std::stringstream os;
    os << num;
    return os.str();
  }
};

class PlusExpression : public Expression
{
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  PlusExpression(Expression * lhs_, Expression * rhs_) : lhs(lhs_), rhs(rhs_) {}
  virtual ~PlusExpression() {
    if (lhs != NULL) {
      delete lhs;
      lhs = NULL;
    }
    if (rhs != NULL) {
      delete rhs;
      rhs = NULL;
    }
  }
  virtual std::string toString() const {
    std::stringstream os;
    os << "(" << lhs->toString() << " + " << rhs->toString() << ")";
    return os.str();
  }
};

#endif
