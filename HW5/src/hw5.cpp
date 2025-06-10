//
// Created by iliya on 06.05.2025.
//

#include "SplayTree.h"
#include <iostream>
#include <string>
#include <sstream>

#define NODE_TO_STRING(node) ((node) != nullptr ? std::to_string((node)->key) : "none")

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string line;
    std::getline(std::cin, line);
    std::istringstream iss(line);
    int n;
    iss >> n;
    SplayTree tree;
    for (int i = 0; i < n; ++i) {
        std::getline(std::cin, line);
        std::istringstream iss(line);
        std::string op;
        iss >> op;
        if (op == "insert") {
            int x;
            iss >> x;
            tree.insert(x);
        } else if (op == "delete") {
            int x;
            iss >> x;
            tree.remove(x);
        } else if (op == "exists") {
            int x;
            iss >> x;
            std::cout << (tree.exists(x) ? "true" : "false") << std::endl;
        } else if (op == "next") {
            int x;
            iss >> x;
            std::cout << NODE_TO_STRING(tree.next(x)) << std::endl;
        } else if (op == "prev") {
            int x;
            iss >> x;
            std::cout << NODE_TO_STRING(tree.prev(x)) << std::endl;
        }
    }
    return 0;
}
