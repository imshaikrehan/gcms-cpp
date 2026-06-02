#ifndef NODE_H
#define NODE_H

template <typename T>
class Node {
public:
    T value;
    Node* left;
    Node* right;
    int height;

    Node(T val) : value(val), left(nullptr), right(nullptr), height(1) {}
};

#endif // NODE_H
