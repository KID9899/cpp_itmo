//
// Created by iliya on 06.06.2025.
//

#ifndef BASE_OPERATIONS_H
#define BASE_OPERATIONS_H

#include "BinaryOperation.h"
#include <stdexcept>
#include <string>

class Add : public BinaryOperation {
public:
    Add(Expression* left, Expression* right) : BinaryOperation(left, right) {}
protected:
    int evaluate(int a, int b) const override {return a + b;}
    std::string getSign() const override {return "+";}
};

class Subtract : public BinaryOperation {
public:
    Subtract(Expression* left, Expression* right) : BinaryOperation(left, right) {}
protected:
    int evaluate(int a, int b) const override {return a - b;}
    std::string getSign() const override {return "-";}
};

class Multiply : public BinaryOperation {
public:
    Multiply(Expression* left, Expression* right) : BinaryOperation(left, right) {}
protected:
    int evaluate(int a, int b) const override {return a * b;}
    std::string getSign() const override {return "*";}
};

class Divide : public BinaryOperation {
public:
    Divide(Expression* left, Expression* right) : BinaryOperation(left, right) {}
protected:
    int evaluate(int a, int b) const override {
        if (b == 0) {
            throw std::runtime_error("Division by zero");
        }
        return a / b;
    }
    std::string getSign() const override {return "/";}
};

#endif // BASE_OPERATIONS_H