//
// Created by iliya on 06.06.2025.
//

#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <string>

class Expression {
public:
    virtual int evaluate(int x) const = 0;
    virtual std::string toString() const = 0;
    virtual ~Expression() = default;
};

#endif // EXPRESSION_H