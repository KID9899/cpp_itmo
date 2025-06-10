//
// Created by iliya on 06.06.2025.
//

#include "Expression.h"
#include "Const.h"
#include "Variable.h"
#include "BaseOperations.h"
#include "Trigonometry.h"
#include <iostream>
#include <stdexcept>

int main() {
    Expression* e1 = new Const(5);
    std::cout << e1->toString() << " = " << e1->evaluate(0) << std::endl;
    delete e1;

    Expression* e2 = new Variable();
    std::cout << e2->toString() << " = " << e2->evaluate(3) << std::endl;
    delete e2;

    Expression* e3 = new Add(new Const(1), new Const(2));
    std::cout << e3->toString() << " = " << e3->evaluate(0) << std::endl;
    delete e3;

    Expression* e4 = new Subtract(new Const(5), new Const(3));
    std::cout << e4->toString() << " = " << e4->evaluate(0) << std::endl;
    delete e4;

    Expression* e5 = new Multiply(new Const(4), new Const(2));
    std::cout << e5->toString() << " = " << e5->evaluate(0) << std::endl;
    delete e5;

    Expression* e6 = new Divide(new Const(10), new Const(2));
    std::cout << e6->toString() << " = " << e6->evaluate(0) << std::endl;
    delete e6;

    Expression* e7 = new Divide(new Const(1), new Const(0));
    try {
        std::cout << e7->toString() << " = " << e7->evaluate(0) << std::endl;
    } catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    delete e7;

    Expression* e8 = new Sin(new Const(0));
    std::cout << e8->toString() << " = " << e8->evaluate(0) << std::endl;
    delete e8;

    Expression* e9 = new Cos(new Const(0));
    std::cout << e9->toString() << " = " << e9->evaluate(0) << std::endl;
    delete e9;

    Expression* e10 = new Add(new Variable(), new Sin(new Variable()));
    std::cout << e10->toString() << " = " << e10->evaluate(3) << std::endl;
    delete e10;

    Expression* e11 = new Multiply(new Add(new Const(1), new Variable()), new Cos(new Const(0)));
    std::cout << e11->toString() << " = " << e11->evaluate(2) << std::endl;
    delete e11;

    return 0;
}