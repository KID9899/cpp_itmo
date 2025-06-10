//
// Created by iliya on 06.06.2025.
//

#ifndef VARIABLE_H
#define VARIABLE_H

#include "Expression.h"
#include <string>

class Variable : public Expression {
public:
    int evaluate(int x) const override {
        return x;
    }
    std::string toString() const override {
        return "x";
    }
};

#endif // VARIABLE_H