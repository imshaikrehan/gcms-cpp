#ifndef AVLTREE_H
#define AVLTREE_H

#include <algorithm>
#include <vector>
#include "Node.h"

template <typename T, typename Comparator>
class AVLTree {
public:
    Node<T>* root;
    Comparator comparator;

    AVLTree() : root(nullptr) {}
    ~AVLTree() {
        destroy_tree(root);
    }

    void destroy_tree(Node<T>* node) {
        if (node) {
            destroy_tree(node->left);
            destroy_tree(node->right);
            delete node;
        }
    }

    int height(Node<T>* node) {
        return node ? node->height : 0;
    }

    int balance(Node<T>* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    Node<T>* right_rotate(Node<T>* z) {
        Node<T>* y = z->left;
        Node<T>* T3 = y->right;

        y->right = z;
        z->left = T3;

        z->height = 1 + std::max(height(z->left), height(z->right));
        y->height = 1 + std::max(height(y->left), height(y->right));

        return y;
    }

    Node<T>* left_rotate(Node<T>* z) {
        Node<T>* y = z->right;
        Node<T>* T2 = y->left;

        y->left = z;
        z->right = T2;

        z->height = 1 + std::max(height(z->left), height(z->right));
        y->height = 1 + std::max(height(y->left), height(y->right));

        return y;
    }

    Node<T>* insert(Node<T>* node, T value) {
        if (!node) return new Node<T>(value);

        if (comparator(node->value, value)) {
            node->left = insert(node->left, value);
        } else {
            node->right = insert(node->right, value);
        }

        node->height = 1 + std::max(height(node->left), height(node->right));
        int b = balance(node);

        if (b > 1 && balance(node->left) >= 0) return right_rotate(node);
        if (b < -1 && balance(node->right) <= 0) return left_rotate(node);
        if (b > 1 && balance(node->left) < 0) {
            node->left = left_rotate(node->left);
            return right_rotate(node);
        }
        if (b < -1 && balance(node->right) > 0) {
            node->right = right_rotate(node->right);
            return left_rotate(node);
        }

        return node;
    }

    Node<T>* min_value_node(Node<T>* node) {
        Node<T>* current = node;
        while (current->left) current = current->left;
        return current;
    }

    Node<T>* delete_node(Node<T>* node, T value) {
        if (!node) return node;

        if (comparator(node->value, value)) {
            node->left = delete_node(node->left, value);
        } else if (comparator(value, node->value)) {
            node->right = delete_node(node->right, value);
        } else {
            if (!node->left || !node->right) {
                Node<T>* temp = node->left ? node->left : node->right;
                if (!temp) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                }
                // Careful here: if node was replaced by temp, we should delete the original temp
                // In simple AVL, we usually just return temp and delete node.
                // Let's do it properly.
                if (temp == node) {
                    delete temp;
                    return nullptr;
                } else {
                    // This part is tricky because of the *node = *temp.
                    // Actually, let's use the standard approach.
                }
            } else {
                Node<T>* temp = min_value_node(node->right);
                node->value = temp->value;
                node->right = delete_node(node->right, temp->value);
            }
        }

        // Standard deletion logic
        if (!node) return node;

        node->height = 1 + std::max(height(node->left), height(node->right));
        int b = balance(node);

        if (b > 1 && balance(node->left) >= 0) return right_rotate(node);
        if (b < -1 && balance(node->right) <= 0) return left_rotate(node);
        if (b > 1 && balance(node->left) < 0) {
            node->left = left_rotate(node->left);
            return right_rotate(node);
        }
        if (b < -1 && balance(node->right) > 0) {
            node->right = right_rotate(node->right);
            return left_rotate(node);
        }

        return node;
    }

    // Re-implementing delete to be safer
    Node<T>* delete_recursive(Node<T>* root, T value) {
        if (root == nullptr) return root;

        if (comparator(root->value, value))
            root->left = delete_recursive(root->left, value);
        else if (comparator(value, root->value))
            root->right = delete_recursive(root->right, value);
        else {
            if ((root->left == nullptr) || (root->right == nullptr)) {
                Node<T>* temp = root->left ? root->left : root->right;
                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                } else
                    *root = *temp;
                delete temp;
            } else {
                Node<T>* temp = min_value_node(root->right);
                root->value = temp->value;
                root->right = delete_recursive(root->right, temp->value);
            }
        }

        if (root == nullptr) return root;

        root->height = 1 + std::max(height(root->left), height(root->right));
        int b = balance(root);

        if (b > 1 && balance(root->left) >= 0) return right_rotate(root);
        if (b > 1 && balance(root->left) < 0) {
            root->left = left_rotate(root->left);
            return right_rotate(root);
        }
        if (b < -1 && balance(root->right) <= 0) return left_rotate(root);
        if (b < -1 && balance(root->right) > 0) {
            root->right = right_rotate(root->right);
            return left_rotate(root);
        }

        return root;
    }

    Node<T>* search(Node<T>* node, int id) {
        if (!node || node->value.id == id) return node;
        if (node->value.id < id) return search(node->right, id);
        return search(node->left, id);
    }

    void insert_value(T value) {
        root = insert(root, value);
    }

    void delete_value(T value) {
        root = delete_recursive(root, value);
    }

    Node<T>* search_value(int id) {
        return search(root, id);
    }

    Node<T>* compact_least(int size) {
        Node<T>* curr = root;
        Node<T>* ans = nullptr;
        while (curr) {
            if (curr->value.capacity >= size) {
                ans = curr;
                curr = curr->left;
            } else {
                curr = curr->right;
            }
        }
        return ans;
    }

    Node<T>* compact_greatest(int size) {
        Node<T>* ans = compact_least(size);
        if (!ans) return nullptr;
        Node<T>* curr = root;
        while (curr) {
            if (curr->value.capacity > ans->value.capacity) {
                curr = curr->left;
            } else if (curr->value.capacity < ans->value.capacity) {
                curr = curr->right;
            } else {
                if (curr->value.id > ans->value.id) {
                    ans = curr;
                }
                curr = curr->right;
            }
        }
        return ans;
    }

    Node<T>* largest_greatest() {
        if (!root) return nullptr;
        Node<T>* curr = root;
        while (curr->right) curr = curr->right;
        return curr;
    }

    Node<T>* largest_least() {
        Node<T>* lg = largest_greatest();
        if (!lg) return nullptr;
        int max_size = lg->value.capacity;
        Node<T>* curr = root;
        Node<T>* ans = lg;
        while (curr) {
            if (curr->value.capacity < max_size) {
                curr = curr->right;
            } else if (curr->value.capacity == max_size) {
                ans = curr;
                curr = curr->left;
            }
        }
        return ans;
    }

    void inorder_ids(Node<T>* node, std::vector<int>& ids) {
        if (!node) return;
        inorder_ids(node->left, ids);
        ids.push_back(node->value.id);
        inorder_ids(node->right, ids);
    }

    std::vector<int> get_inorder_ids() {
        std::vector<int> ids;
        inorder_ids(root, ids);
        return ids;
    }
};

#endif // AVLTREE_H
