//
// Created by iliya on 09.06.2025.
//

#ifndef BINARY_OPERATION_H
#define BINARY_OPERATION_H

#include "Expression.h"
#include <string>

class BinaryOperation : public Expression {
private:
    Expression* l;
    Expression* r;
protected:
    virtual std::string getSign() const = 0;
    virtual int evaluate(int a, int b) const = 0;
public:
    BinaryOperation(Expression* left, Expression* right) : l(left), r(right) {}
    ~BinaryOperation() override {
        delete l;
        delete r;
    }
    int evaluate(int x) const override {
        return evaluate(l->evaluate(x), r->evaluate(x));
    }
    std::string toString() const override {
        return "(" + l->toString() + " " + getSign() + " " + r->toString() + ")";
    }
};

#endif //BINARY_OPERATION_H
