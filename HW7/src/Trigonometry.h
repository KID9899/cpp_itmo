//
// Created by iliya on 06.06.2025.
//

#ifndef TRIGONOMETRY_H
#define TRIGONOMETRY_H

#include "UnaryOperation.h"
#include <string>
#include <cmath>

class Sin : public UnaryOperation {
public:
    Sin(Expression* inner) : UnaryOperation(inner) {}
protected:
    int evaluateInner(int inner) const override {return static_cast<int>(std::sin(inner));}
    std::string getSign() const override {return "sin";}
    bool isLeft() const override {return true;}
};

class Cos : public UnaryOperation {
public:
    Cos(Expression* inner) : UnaryOperation(inner) {}
protected:
    int evaluateInner(int inner) const override {return static_cast<int>(std::cos(inner));}
    std::string getSign() const override {return "cos";}
    bool isLeft() const override {return true;}
};

#endif // TRIGONOMETRY_H