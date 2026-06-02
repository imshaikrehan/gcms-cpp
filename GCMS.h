#ifndef GCMS_H
#define GCMS_H

#include <vector>
#include <tuple>
#include "AVLTree.h"
#include "Bin.h"
#include "Object.h"
#include "Exceptions.h"

struct IDComparator {
    bool operator()(const Bin& a, const Bin& b) const {
        return a.id > b.id;
    }
    bool operator()(const Object& a, const Object& b) const {
        return a.id > b.id;
    }
};

struct CapacityComparator {
    bool operator()(const Bin& a, const Bin& b) const {
        if (a.capacity != b.capacity) {
            return a.capacity > b.capacity;
        }
        return a.id > b.id;
    }
};

class GCMS {
public:
    AVLTree<Bin, IDComparator> avl_bin;
    AVLTree<Object, IDComparator> avl_object;
    AVLTree<Bin, CapacityComparator> avl_search;

    GCMS() {}

    void add_bin(int bin_id, int capacity);
    void add_object(int object_id, int size, Color color);
    void delete_object(int object_id);
    std::pair<int, std::vector<int>> bin_info(int bin_id);
    int object_info(int object_id);
};

#endif // GCMS_H
