//
// Created by iliya on 06.05.2025.
//

#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#include <string>
#include <utility>
#include <type_traits>
#include <stdexcept>

struct SetTag {};

template <typename Key, typename Value = SetTag>
class SplayTree {
private:
    using Data = typename std::conditional<std::is_same<Value, SetTag>::value, Key, std::pair<Key, Value>>::type;
public:
    struct Node {
        Data data;
        Node* left;
        Node* right;
        Node* parent;
        Node(const Data& d) : data(d), left(nullptr), right(nullptr), parent(nullptr) {}
    };
private:
    Node* root;

    void rotateLeft(Node* p);
    void rotateRight(Node* p);
    void splay(Node* node);
    Node* insertBST(const Data& d);
    Node* findMax(Node* node);
    Node* search(const Key& k);
    void deleteTree(Node* node);

    const Key& getKey(const Data& d) const {
        if constexpr (std::is_same<Value, SetTag>::value) {
            return d;
        } else {
            return d.first;
        }
    }

public:
    SplayTree() : root(nullptr) {}
    ~SplayTree();

    template <typename V = Value>
    typename std::enable_if<!std::is_same<V, SetTag>::value>::type
    insert(const Key& k, const V& v) {
        Data d = {k, v};
        Node* node = insertBST(d);
        splay(node);
    }

    template <typename V = Value>
    typename std::enable_if<std::is_same<V, SetTag>::value>::type
    insert(const Key& k) {
        Data d = k;
        Node* node = insertBST(d);
        splay(node);
    }

    void remove(const Key& k);
    bool exists(const Key& k);
    Node* next(const Key& k);
    Node* prev(const Key& k);

    template <typename V = Value>
    typename std::enable_if<!std::is_same<V, SetTag>::value, Value&>::type at(const Key& k) {
        Node* node = search(k);
        if (node) {
            return node->data.second;
        }
        throw std::out_of_range("Key not found");
    }
};

#endif // SPLAYTREE_H