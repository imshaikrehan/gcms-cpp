#include <iostream>
#include <vector>
#include "GCMS.h"
#include "Object.h"

int main() {
    GCMS gcms;

    gcms.add_bin(1234, 10);
    gcms.add_bin(4321, 20);
    gcms.add_bin(1111, 15);

    try {
        gcms.add_object(8989, 6, Color::RED);
    } catch (const std::exception& e) {
        std::cout << "Object 1 was not able to be added" << std::endl;
    }

    try {
        gcms.add_object(2892, 8, Color::RED);
    } catch (const std::exception& e) {
        std::cout << "Object 2 was not able to be added" << std::endl;
    }

    try {
        gcms.add_object(4839, 9, Color::RED);
    } catch (const std::exception& e) {
        std::cout << "Object 3 was not able to be added" << std::endl;
    }

    try {
        gcms.add_object(3283, 2, Color::RED);
    } catch (const std::exception& e) {
        std::cout << "Object 4 was not able to be added" << std::endl;
    }

    try {
        gcms.add_object(8983, 8, Color::RED);
    } catch (const std::exception& e) {
        std::cout << "Object 5 was not able to be added" << std::endl;
    }

    auto info1 = gcms.bin_info(1234);
    std::cout << "(" << info1.first << ", [";
    for (size_t i = 0; i < info1.second.size(); ++i) {
        std::cout << info1.second[i] << (i == info1.second.size() - 1 ? "" : ", ");
    }
    std::cout << "])" << std::endl;

    auto info2 = gcms.bin_info(4321);
    std::cout << "(" << info2.first << ", [";
    for (size_t i = 0; i < info2.second.size(); ++i) {
        std::cout << info2.second[i] << (i == info2.second.size() - 1 ? "" : ", ");
    }
    std::cout << "])" << std::endl;

    std::cout << "Object 8989 info: " << gcms.object_info(8989) << std::endl;
    std::cout << "Deleting object 8989..." << std::endl;
    gcms.delete_object(8989);
    std::cout << "Object 8989 info after deletion: " << gcms.object_info(8989) << std::endl;

    auto info2_after = gcms.bin_info(4321);
    std::cout << "Bin 4321 after deleting 8989: (" << info2_after.first << ", [";
    for (size_t i = 0; i < info2_after.second.size(); ++i) {
        std::cout << info2_after.second[i] << (i == info2_after.second.size() - 1 ? "" : ", ");
    }
    std::cout << "])" << std::endl;

    return 0;
}
