#ifndef __EXPR_H__
#define __EXPR_H__

#include <cassert>
#include <iostream>
#include <sstream>
#include <string>

class Expression
{
 public:
  virtual ~Expression() {}
  virtual std::string toString() const = 0;
  virtual long evaluate() const = 0;
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
  virtual long evaluate() const { return num; }
};

class BinaryExpression : public Expression
{
 protected:
  Expression * lhs;
  Expression * rhs;

 public:
  BinaryExpression(Expression * lhs_, Expression * rhs_) : lhs(lhs_), rhs(rhs_) {}
  virtual ~BinaryExpression() {
    if (lhs != NULL) {
      delete lhs;
      lhs = NULL;
    }
    if (rhs != NULL) {
      delete rhs;
      rhs = NULL;
    }
  }
};

class PlusExpression : public BinaryExpression
{
 public:
  PlusExpression(Expression * lhs_, Expression * rhs_) : BinaryExpression(lhs_, rhs_) {}
  virtual std::string toString() const {
    std::stringstream os;
    os << "(" << lhs->toString() << " + " << rhs->toString() << ")";
    return os.str();
  }
  virtual long evaluate() const {
    long lLhs = lhs->evaluate();
    long lRhs = rhs->evaluate();
    return lLhs + lRhs;
  }
};

class MinusExpression : public BinaryExpression
{
 public:
  MinusExpression(Expression * lhs_, Expression * rhs_) : BinaryExpression(lhs_, rhs_) {}
  virtual std::string toString() const {
    std::stringstream os;
    os << "(" << lhs->toString() << " - " << rhs->toString() << ")";
    return os.str();
  }
  virtual long evaluate() const {
    long lLhs = lhs->evaluate();
    long lRhs = rhs->evaluate();
    return lLhs - lRhs;
  }
};

class TimesExpression : public BinaryExpression
{
 public:
  TimesExpression(Expression * lhs_, Expression * rhs_) : BinaryExpression(lhs_, rhs_) {}
  virtual std::string toString() const {
    std::stringstream os;
    os << "(" << lhs->toString() << " * " << rhs->toString() << ")";
    return os.str();
  }
  virtual long evaluate() const {
    long lLhs = lhs->evaluate();
    long lRhs = rhs->evaluate();
    return lLhs * lRhs;
  }
};

class DivExpression : public BinaryExpression
{
 public:
  DivExpression(Expression * lhs_, Expression * rhs_) : BinaryExpression(lhs_, rhs_) {}
  virtual std::string toString() const {
    std::stringstream os;
    os << "(" << lhs->toString() << " / " << rhs->toString() << ")";
    return os.str();
  }
  virtual long evaluate() const {
    long lLhs = lhs->evaluate();
    long lRhs = rhs->evaluate();
    assert(lRhs != 0);
    return lLhs / lRhs;
  }
};

#endif
