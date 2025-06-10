//
// Created by iliya on 06.05.2025.
//

#include "SplayTree.h"
#include <limits>

SplayTree::~SplayTree() {
    if (root != nullptr) delete root;
}

void SplayTree::rotateLeft(Node* p) {
    if (!p || !p->right) return;
    Node* c = p->right;
    p->right = c->left;
    if (c->left) c->left->parent = p;
    c->parent = p->parent;
    if (p->parent) {
        if (p->parent->left == p) p->parent->left = c;
        else p->parent->right = c;
    } else {
        root = c;
    }
    c->left = p;
    p->parent = c;
}

void SplayTree::rotateRight(Node* p) {
    if (!p || !p->left) return;
    Node* c = p->left;
    p->left = c->right;
    if (c->right) c->right->parent = p;
    c->parent = p->parent;
    if (p->parent) {
        if (p->parent->left == p) p->parent->left = c;
        else p->parent->right = c;
    } else {
        root = c;
    }
    c->right = p;
    p->parent = c;
}

void SplayTree::splay(Node* node) {
    while (node->parent != nullptr) {
        Node* parent = node->parent;
        if (parent->parent == nullptr) {
            if (parent->left == node) {
                rotateRight(parent);
            } else {
                rotateLeft(parent);
            }
        } else {
            Node* grandparent = parent->parent;
            if (grandparent->left == parent && parent->left == node) {
                rotateRight(grandparent);
                rotateRight(parent);
            } else if (grandparent->right == parent && parent->right == node) {
                rotateLeft(grandparent);
                rotateLeft(parent);
            } else if (grandparent->left == parent && parent->right == node) {
                rotateLeft(parent);
                rotateRight(grandparent);
            } else if (grandparent->right == parent && parent->left == node) {
                rotateRight(parent);
                rotateLeft(grandparent);
            }
        }
    }
}

SplayTree::Node* SplayTree::insertBST(SplayTree::element_t x) {
    Node* current = root;
    Node* parent = nullptr;
    while (current != nullptr) {
        parent = current;
        if (x < current->key) {
            current = current->left;
        } else if (x > current->key) {
            current = current->right;
        } else {
            return current;
        }
    }
    Node* newNode = new Node(x);
    newNode->parent = parent;
    if (parent == nullptr) {
        root = newNode;
    } else if (x < parent->key) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }
    return newNode;
}

void SplayTree::insert(SplayTree::element_t x) {
    Node* node = insertBST(x);
    splay(node);
}

SplayTree::Node* SplayTree::search(SplayTree::element_t x) {
    if (root == nullptr) {
        return nullptr;
    }
    Node* current = root;
    Node* last = nullptr;
    while (current != nullptr) {
        last = current;
        if (x < current->key) {
            current = current->left;
        } else if (x > current->key) {
            current = current->right;
        } else {
            splay(current);
            return current;
        }
    }
    splay(last);
    return nullptr;
}

bool SplayTree::exists(SplayTree::element_t x) {
    return search(x) != nullptr;
}

void SplayTree::remove(SplayTree::element_t x) {
    Node* node = search(x);
    if (node == nullptr) {
        return;
    }
    Node* L = node->left;
    Node* R = node->right;
    if (L == nullptr) {
        root = R;
        if (R) R->parent = nullptr;
    } else if (R == nullptr) {
        root = L;
        if (L) L->parent = nullptr;
    } else {
        Node* M = findMax(L);
        root = L;
        L->parent = nullptr;
        splay(M);
        M->right = R;
        if (R) R->parent = M;
        root = M;
    }
    delete node;
}

SplayTree::Node* SplayTree::findMax(Node* node) {
    while (node->right != nullptr) {
        node = node->right;
    }
    return node;
}

SplayTree::Node* SplayTree::next(SplayTree::element_t x) {
    Node* current = root;
    Node* successor = nullptr;
    Node* last = nullptr;
    while (current != nullptr) {
        last = current;
        if (current->key > x) {
            successor = current;
            current = current->left;
        } else {
            current = current->right;
        }
    }
    if (successor != nullptr) {
        splay(successor);
        return successor;
    } else {
        if (last != nullptr) {
            splay(last);
        }
        return nullptr;
    }
}

SplayTree::Node* SplayTree::prev(SplayTree::element_t x) {
    Node* current = root;
    Node* predecessor = nullptr;
    Node* last = nullptr;
    while (current != nullptr) {
        last = current;
        if (current->key < x) {
            predecessor = current;
            current = current->right;
        } else {
            current = current->left;
        }
    }
    if (predecessor != nullptr) {
        splay(predecessor);
        return predecessor;
    } else {
        if (last != nullptr) {
            splay(last);
        }
        return nullptr;
    }
}
