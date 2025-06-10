//
// Created by iliya on 06.05.2025.
//

#include "BigInteger.h"
#include <iostream>
#include <string>
#include <stdexcept>

struct Expression {
    BigInteger a;
    char op;
    BigInteger b;
};

bool isValidNumber(const std::string& s) {
    if (s.empty()) return false;
    size_t start = 0;
    if (s[0] == '-') start = 1;
    if (start == s.size()) return false;
    for (size_t i = start; i < s.size(); ++i) {
        if (!isdigit(s[i])) return false;
    }
    return true;
}

Expression parseExpression(const std::string& s) {
    for (size_t i = 1; i < s.size(); ++i) {
        char c = s[i];
        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%') {
            std::string left = s.substr(0, i);
            std::string right = s.substr(i + 1);
            if (isValidNumber(left) && isValidNumber(right)) {
                return {BigInteger(left), c, BigInteger(right)};
            }
        }
    }
    throw std::invalid_argument("Invalid expression");
}

int main() {
    std::string input;
    std::getline(std::cin, input);
    try {
        Expression expr = parseExpression(input);
        BigInteger result;
        switch (expr.op) {
            case '+': result = expr.a + expr.b; break;
            case '-': result = expr.a - expr.b; break;
            case '*': result = expr.a * expr.b; break;
            case '/': result = expr.a / expr.b; break;
            case '%': result = expr.a % expr.b; break;
            default: throw std::invalid_argument("Invalid operator");
        }
        std::cout << result.toString() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
