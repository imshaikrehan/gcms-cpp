#ifndef BIN_H
#define BIN_H

#include <memory>
#include "Object.h"
#include "Node.h"

// Forward declaration
template <typename T, typename Comparator>
class AVLTree;

struct ObjectComparator {
    bool operator()(const Object& a, const Object& b) const {
        return a.id > b.id;
    }
};

#include "AVLTree.h"

class Bin {
public:
    int id;
    int capacity;
    std::shared_ptr<AVLTree<Object, ObjectComparator>> avl_inside_bin;

    Bin(int bin_id, int bin_capacity);
    // Destructor doesn't need to delete avl_inside_bin anymore
    ~Bin() = default;

    void add_object(Object obj);
    void remove_object(int object_id);
};

#endif // BIN_H
