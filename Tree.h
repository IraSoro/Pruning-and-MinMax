#ifndef TREE_H
#define TREE_H

#include "iostream"

struct Node{
    Node(int count) {
        this->count = count;
        for(int i = 0; i < count; i++)
            arrayChildren[i] = nullptr;
    }
    Node() {
        count = 0;
        for(int i = 0; i < count; i++)
            arrayChildren[i] = nullptr;
    }
    int count = 0;
    Node* arrayChildren[];
};


#endif // TREE_H
