#ifndef TEST_TASK_AVLTREE_H
#define TEST_TASK_AVLTREE_H

#include <algorithm>
#include <iostream>
#include <utility>
#include <deque>
#include "Container.h"

template<class K, class D>
class Node {
    K key;
    D data;
    Node<K, D> *left;
    Node<K, D> *right;
    int height;

    template<class Key, class Data>
    friend
    class AVLTree;
};

template<class Key, class Data>
class AVLTree : public Container<Key, Data> {
public:
    AVLTree() {
        root = nullptr;
        node_count = 0;
        topn_array = nullptr;
    };

    ~AVLTree() {
        deleteTree(root);
        if (!topn_array)
            delete[] topn_array;
    }

    void add(Key x, Data y) {
        root = insert(x, y, root);
        node_count++;
    }

    void remove(Key x) {
        root = remove(x, root);
        node_count--;
    }

    void display() {
        inorder(root);
        std::cout << std::endl;
    }

    unsigned long long get_sum_amount() {
        return DfsSumAmount(root, 0);
    }

    Data get(Key price) {
        Node<Key, Data> *temp = find(root, price);
        return temp ? temp->data : 0;
    }

    std::pair<Key, Data> get_first() const {
        return std::make_pair(root->key, root->data);
    }

    std::pair<Key, Data> *topn(long long n) {
        long long i = 0;
        if (n > node_count)
            this->set_topn_size(node_count);
        else
            this->set_topn_size(n);
        delete[] topn_array;
        long long topn_array_size = this->get_topn_size();
        topn_array = new std::pair<long long, long long>[topn_array_size];
        reverseOrder(root, topn_array_size, i, topn_array);
        return topn_array;
    }

private:
    Node<Key, Data> *root;
    unsigned long long node_count;
    std::pair<Key, Data> *topn_array;

    Node<Key, Data> *insert(Key x, Data y, Node<Key, Data> *t) {
        if (t == nullptr) {
            t = new Node<Key, Data>;
            t->key = x;
            t->data = y;
            t->height = 0;
            t->left = t->right = nullptr;
        } else if (x < t->key) {
            t->left = insert(x, y, t->left);
        } else if (x > t->key) {
            t->right = insert(x, y, t->right);
        } else {
            t->data = y;
            return t;
        }

        balance(t);

        t->height = std::max(height(t->left), height(t->right)) + 1;
        return t;
    }

    Node<Key, Data> *remove(Key x, Node<Key, Data> *t) {
        if (!t)
            return 0;
        if (x < t->key)
            t->left = remove(x, t->left);
        else if (x > t->key)
            t->right = remove(x, t->right);
        else //  k == p->key
        {
            Node<Key, Data> *q = t->left;
            Node<Key, Data> *r = t->right;
            delete t;
            if (!r) return q;
            Node<Key, Data> *min = findMin(r);
            min->right = removeMin(r);
            min->left = q;
            return balance(min);
        }
        return balance(t);
    }

    Node<Key, Data> *singleRightRotate(Node<Key, Data> *&t) {
        Node<Key, Data> *u = t->left;
        t->left = u->right;
        u->right = t;
        t->height = std::max(height(t->left), height(t->right)) + 1;
        u->height = std::max(height(u->left), t->height) + 1;
        return u;
    }

    Node<Key, Data> *singleLeftRotate(Node<Key, Data> *&t) {
        Node<Key, Data> *u = t->right;
        t->right = u->left;
        u->left = t;
        t->height = std::max(height(t->left), height(t->right)) + 1;
        u->height = std::max(height(t->right), t->height) + 1;
        return u;
    }

    Node<Key, Data> *findMin(Node<Key, Data> *t) {
        if (t->left) {
            return findMin(t->left);
        } else {
            return t;
        }
    }

    Node<Key, Data> *removeMin(Node<Key, Data> *p) {
        if (p->left == nullptr)
            return p->right;
        p->left = removeMin(p->left);
        return balance(p);
    }

    void inorder(Node<Key, Data> *t) {
        if (t == nullptr)
            return;
        inorder(t->left);
        std::cout << t->key << " ";
        inorder(t->right);
    }

    void deleteTree(Node<Key, Data> *node) {
        if (node == nullptr) return;

        deleteTree(node->left);
        deleteTree(node->right);

        delete node;
    }

    inline int height(Node<Key, Data> *t) {
        if (t == nullptr) {
            return 0;
        } else {
            return t->height;
        }
    }

    inline int getBalance(Node<Key, Data> *t) {
        if (t == nullptr)
            return 0;
        else
            return height(t->left) - height(t->right);
    }

    Node<Key, Data> *balance(Node<Key, Data> *p) {
        p->height = std::max(height(p->left), height(p->right)) + 1;
        if (getBalance(p) == -2) {
            if (getBalance(p->right) > 0)
                p->right = singleRightRotate(p->right);
            return singleLeftRotate(p);
        }
        if (getBalance(p) == 2) {
            if (getBalance(p->left) < 0)
                p->left = singleLeftRotate(p->left);
            return singleRightRotate(p);
        }
        return p;
    }

    unsigned long long DfsSumAmount(Node<Key, Data> *t, unsigned long long sum) {
        if (t == nullptr)
            return sum;
        sum += t->key;
        DfsSumAmount(t->left, sum);
        DfsSumAmount(t->right, sum);
    }

    Node<Key, Data> *find(Node<Key, Data> *node, Key key) {
        if (node == nullptr)
            return nullptr;
        if (key == node->key)
            return node;
        find(node->left, key);
        find(node->right, key);
    }

    std::pair<Key, Data> *reverseOrder(Node<Key, Data> *node, long long &n, long long &i, std::pair<Key, Data> *array) {
        if (node == nullptr)
            return nullptr;
        reverseOrder(node->right, n, i, array);
        if (i < n)
            array[i++] = std::make_pair(node->key, node->data);
        reverseOrder(node->left, n, i, array);
    }
};

#endif //TEST_TASK_AVLTREE_H
