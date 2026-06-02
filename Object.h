#ifndef OBJECT_H
#define OBJECT_H

enum class Color {
    BLUE = 1,
    YELLOW = 2,
    RED = 3,
    GREEN = 4
};

class Object {
public:
    int id;
    int size;
    Color color;
    int bin_id_appended;

    Object(int object_id, int object_size = 0, Color object_color = Color::BLUE)
        : id(object_id), size(object_size), color(object_color), bin_id_appended(-1) {}
};

#endif // OBJECT_H
