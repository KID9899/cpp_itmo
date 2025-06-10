//
// Created by iliya on 06.05.2025.
//

#include "SplayTree.h"
#include <limits>

template <typename Key, typename Value>
SplayTree<Key, Value>::~SplayTree() {
    deleteTree(root);
}

template <typename Key, typename Value>
void SplayTree<Key, Value>::deleteTree(Node* node) {
    if (node) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

template <typename Key, typename Value>
void SplayTree<Key, Value>::rotateLeft(Node* p) {
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

template <typename Key, typename Value>
void SplayTree<Key, Value>::rotateRight(Node* p) {
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

template <typename Key, typename Value>
void SplayTree<Key, Value>::splay(Node* node) {
    while (node->parent) {
        Node* parent = node->parent;
        if (!parent->parent) {
            if (parent->left == node) {
                rotateRight(parent);
            } else {
                rotateLeft(parent);
            }
        } else {
            Node* grand = parent->parent;
            if (grand->left == parent && parent->left == node) {
                rotateRight(grand);
                rotateRight(parent);
            } else if (grand->right == parent && parent->right == node) {
                rotateLeft(grand);
                rotateLeft(parent);
            } else if (grand->left == parent && parent->right == node) {
                rotateLeft(parent);
                rotateRight(grand);
            } else {
                rotateRight(parent);
                rotateLeft(grand);
            }
        }
    }
}

template <typename Key, typename Value>
typename SplayTree<Key, Value>::Node* SplayTree<Key, Value>::insertBST(const Data& d) {
    Node* curr = root;
    Node* par = nullptr;
    while (curr) {
        par = curr;
        if (getKey(d) < getKey(curr->data)) {
            curr = curr->left;
        } else if (getKey(d) > getKey(curr->data)) {
            curr = curr->right;
        } else {
            if constexpr (!std::is_same<Value, SetTag>::value) {
                curr->data.second = d.second;
            }
            return curr;
        }
    }
    Node* newNode = new Node(d);
    newNode->parent = par;
    if (!par) {
        root = newNode;
    } else if (getKey(d) < getKey(par->data)) {
        par->left = newNode;
    } else {
        par->right = newNode;
    }
    return newNode;
}

template <typename Key, typename Value>
typename SplayTree<Key, Value>::Node* SplayTree<Key, Value>::search(const Key& k) {
    if (!root) return nullptr;
    Node* curr = root;
    Node* last = nullptr;
    while (curr) {
        last = curr;
        if (k < getKey(curr->data)) {
            curr = curr->left;
        } else if (k > getKey(curr->data)) {
            curr = curr->right;
        } else {
            splay(curr);
            return curr;
        }
    }
    splay(last);
    return nullptr;
}

template <typename Key, typename Value>
bool SplayTree<Key, Value>::exists(const Key& k) {
    return search(k) != nullptr;
}

template <typename Key, typename Value>
void SplayTree<Key, Value>::remove(const Key& k) {
    Node* node = search(k);
    if (!node) return;
    Node* L = node->left;
    Node* R = node->right;
    if (!L) {
        root = R;
        if (R) R->parent = nullptr;
    } else if (!R) {
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

template <typename Key, typename Value>
typename SplayTree<Key, Value>::Node* SplayTree<Key, Value>::findMax(Node* node) {
    while (node->right) {
        node = node->right;
    }
    return node;
}

template <typename Key, typename Value>
typename SplayTree<Key, Value>::Node* SplayTree<Key, Value>::next(const Key& k) {
    Node* curr = root;
    Node* succ = nullptr;
    Node* last = nullptr;
    while (curr) {
        last = curr;
        if (getKey(curr->data) > k) {
            succ = curr;
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    if (succ) {
        splay(succ);
        return succ;
    }
    if (last) splay(last);
    return nullptr;
}

template <typename Key, typename Value>
typename SplayTree<Key, Value>::Node* SplayTree<Key, Value>::prev(const Key& k) {
    Node* curr = root;
    Node* pred = nullptr;
    Node* last = nullptr;
    while (curr) {
        last = curr;
        if (getKey(curr->data) < k) {
            pred = curr;
            curr = curr->right;
        } else {
            curr = curr->left;
        }
    }
    if (pred) {
        splay(pred);
        return pred;
    }
    if (last) splay(last);
    return nullptr;
}

template class SplayTree<int>;
template class SplayTree<int, std::string>;
