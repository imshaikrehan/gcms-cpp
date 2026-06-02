#include "GCMS.h"

void GCMS::add_bin(int bin_id, int capacity) {
    Bin bin_instance(bin_id, capacity);
    avl_bin.insert_value(bin_instance);
    avl_search.insert_value(bin_instance);
}

void GCMS::add_object(int object_id, int size, Color color) {
    Node<Bin>* node = nullptr;
    if (color == Color::BLUE) {
        node = avl_search.compact_least(size);
    } else if (color == Color::YELLOW) {
        node = avl_search.compact_greatest(size);
    } else if (color == Color::RED) {
        node = avl_search.largest_least();
    } else {
        node = avl_search.largest_greatest();
    }

    if (!node || node->value.capacity < size) {
        throw NoBinFoundException();
    }

    int bin_id = node->value.id;
    int old_capacity = node->value.capacity;

    Object object_instance(object_id, size, color);
    object_instance.bin_id_appended = bin_id;
    avl_object.insert_value(object_instance);

    // Update avl_search
    Bin bin_to_delete(bin_id, old_capacity);
    avl_search.delete_value(bin_to_delete);
    
    Bin bin_to_insert(bin_id, old_capacity - size);
    // We need to keep the same avl_inside_bin for this bin ID
    // So we should find it in avl_bin first
    Node<Bin>* bin_node = avl_bin.search_value(bin_id);
    bin_to_insert.avl_inside_bin = bin_node->value.avl_inside_bin;
    avl_search.insert_value(bin_to_insert);

    // Update avl_bin
    bin_node->value.capacity -= size;
    bin_node->value.add_object(object_instance);
}

void GCMS::delete_object(int object_id) {
    Node<Object>* obj_node = avl_object.search_value(object_id);
    if (!obj_node) return;

    int bin_id = obj_node->value.bin_id_appended;
    int object_size = obj_node->value.size;

    avl_object.delete_value(Object(object_id));

    Node<Bin>* bin_node = avl_bin.search_value(bin_id);
    int old_capacity = bin_node->value.capacity;

    // Update avl_search
    Bin bin_to_delete(bin_id, old_capacity);
    avl_search.delete_value(bin_to_delete);

    bin_node->value.capacity += object_size;
    bin_node->value.remove_object(object_id);

    Bin bin_to_insert(bin_id, old_capacity + object_size);
    bin_to_insert.avl_inside_bin = bin_node->value.avl_inside_bin;
    avl_search.insert_value(bin_to_insert);
}

std::pair<int, std::vector<int>> GCMS::bin_info(int bin_id) {
    Node<Bin>* node = avl_bin.search_value(bin_id);
    if (!node) return {0, {}};
    return {node->value.capacity, node->value.avl_inside_bin->get_inorder_ids()};
}

int GCMS::object_info(int object_id) {
    Node<Object>* node = avl_object.search_value(object_id);
    if (!node) return -1;
    return node->value.bin_id_appended;
}
