//
// Created by iliya on 06.05.2025.
//

#include "SplayTree.h"
#include <iostream>
#include <string>
#include <sstream>

template <typename Key, typename Value>
const std::string getKey(const typename SplayTree<Key, Value>::Node* d) {
    if (!d) return "none";
    if constexpr (std::is_same<Value, SetTag>::value) {
        return std::to_string(d->data);
    } else {
        return std::to_string(d->data.first);
    }
}

void check(bool condition, const std::string& message) {
    std::cout << (condition ? "PASS" : "FAIL") << ": " << message << std::endl;
}

void testSet() {
    SplayTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);

    check(tree.exists(5), "5 exists");
    check(tree.exists(3), "3 exists");
    check(tree.exists(7), "7 exists");
    check(tree.exists(2), "2 exists");
    check(tree.exists(4), "4 exists");
    check(tree.exists(6), "6 exists");
    check(tree.exists(8), "8 exists");
    check(!tree.exists(1), "1 does not exist");
    check(!tree.exists(9), "9 does not exist");

    tree.remove(3);
    check(!tree.exists(3), "3 deleted");
    check(tree.exists(5), "5 still exists");

    auto n = tree.next(4);
    check(getKey<int, SetTag>(n) == "5", "next of 4 is 5");
    n = tree.next(8);
    check(!n, "next of 8 is none");
    n = tree.next(1);
    check(getKey<int, SetTag>(n) == "2", "next of 1 is 2");

    n = tree.prev(4);
    check(getKey<int, SetTag>(n) == "2", "prev of 4 is 2");
    n = tree.prev(2);
    check(!n, "prev of 2 is none");
    n = tree.prev(9);
    check(getKey<int, SetTag>(n) == "8", "prev of 9 is 8");

    tree.insert(5);
    check(tree.exists(5), "5 still exists after duplicate insert");

    tree.remove(9);
    check(!tree.exists(9), "9 still does not exist");

    SplayTree<int> emptyTree;
    n = emptyTree.next(0);
    check(getKey<int, SetTag>(n) == "none", "next in empty tree is none");
    n = emptyTree.prev(0);
    check(getKey<int, SetTag>(n) == "none", "prev in empty tree is none");
}

void testMap() {
    SplayTree<int, std::string> map;
    map.insert(5, "five");
    map.insert(3, "three");
    map.insert(7, "seven");

    check(map.at(5) == "five", "at(5) == five");
    check(map.at(3) == "three", "at(3) == three");
    check(map.at(7) == "seven", "at(7) == seven");

    map.insert(5, "cinco");
    check(map.at(5) == "cinco", "at(5) == cinco after update");

    map.remove(3);
    check(!map.exists(3), "3 deleted");
    check(map.at(5) == "cinco", "at(5) still cinco");
    check(map.at(7) == "seven", "at(7) still seven");

    try {
        map.at(3);
        check(false, "at(3) should throw");
    } catch (const std::out_of_range&) {
        check(true, "at(3) throws out_of_range");
    }

    auto n = map.next(4);
    check(getKey<int, std::string>(n) == "5", "next of 4 is 5");
    n = map.next(7);
    check(getKey<int, std::string>(n) == "none", "next of 7 is none");

    n = map.prev(6);
    check(getKey<int, std::string>(n) == "5", "prev of 6 is 5");
    n = map.prev(3);
    check(getKey<int, std::string>(n) == "none", "prev of 3 is none");

    SplayTree<int, std::string> emptyMap;
    n = emptyMap.next(0);
    check(getKey<int, std::string>(n) == "none", "next in empty map is none");
    n = emptyMap.prev(0);
    check(getKey<int, std::string>(n) == "none", "prev in empty map is none");
}

int main() {
    std::cout << "Testing Set:" << std::endl;
    testSet();
    std::cout << "\nTesting Map:" << std::endl;
    testMap();
    return 0;
}