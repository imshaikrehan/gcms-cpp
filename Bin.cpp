#include "Bin.h"
#include "AVLTree.h"

Bin::Bin(int bin_id, int bin_capacity) : id(bin_id), capacity(bin_capacity) {
    avl_inside_bin = std::make_shared<AVLTree<Object, ObjectComparator>>();
}

void Bin::add_object(Object obj) {
    avl_inside_bin->insert_value(obj);
}

void Bin::remove_object(int object_id) {
    Object temp_obj(object_id);
    avl_inside_bin->delete_value(temp_obj);
}
