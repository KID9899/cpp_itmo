//
// Created by iliya on 09.06.2025.
//

#ifndef UNARY_OPERATION_H
#define UNARY_OPERATION_H

#include "Expression.h"
#include <string>

class UnaryOperation : public Expression {
private:
    Expression* inner;
protected:
    virtual std::string getSign() const = 0;
    virtual bool isLeft() const = 0;
    virtual int evaluateInner(int inner) const = 0;
public:
    UnaryOperation(Expression* inner) : inner(inner) {}
    ~UnaryOperation() override {
        delete inner;
    }
    int evaluate(int x) const override {
        return evaluateInner(inner->evaluate(x));
    }
    std::string toString() const override {
        std::string prefix = isLeft() ? getSign() : "";
        std::string suffix = isLeft() ? "" : getSign();
        return prefix + "(" + inner->toString() + ")" + suffix;
    }
};

#endif // UNARY_OPERATION_H
