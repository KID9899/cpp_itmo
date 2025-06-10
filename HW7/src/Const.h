//
// Created by iliya on 06.06.2025.
//

#ifndef CONST_H
#define CONST_H

#include "Expression.h"
#include <string>

class Const : public Expression {
private:
    int val;
public:
    Const(int v) : val(v) {}
    int evaluate(int x) const override {
        return val;
    }
    std::string toString() const override {
        return std::to_string(val);
    }
};

#endif // CONST_H