//
// Created by iliya on 06.05.2025.
//

#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#include <string>

class SplayTree {
    using element_t = int;
    struct Node {
        ~Node() {
            if (left != nullptr) delete left;
            if (right != nullptr) delete right;
        }
        element_t key;
        Node* left;
        Node* right;
        Node* parent;
        Node(element_t k) : key(k), left(nullptr), right(nullptr), parent(nullptr) {};
    };
private:

    Node* root;
    void rotateLeft(Node* p);
    void rotateRight(Node* p);
    void splay(Node* node);
    Node* insertBST(element_t x);
    Node* findMax(Node* node);
    Node* search(element_t x);
    void deleteTree(Node* node);

public:
    SplayTree() : root(nullptr) {};
    ~SplayTree();
    void insert(element_t x);
    void remove(element_t x);
    bool exists(element_t x);
    Node* next(element_t x);
    Node* prev(element_t x);
};

#endif // SPLAYTREE_H
