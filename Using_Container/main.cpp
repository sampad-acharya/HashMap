#include <iostream>
#include <vector>
#include <utility>
#include <functional>
#include "HashMapContainer.hpp"


int main() {
    HashMap<std::string, int> map{10};
    map.insert("apple", 10);
    map.insert("banana", 20);
    map.insert("orange", 30);

    map.print();

    map.erase("banana");
    map["lemon"] = 40;
    map.print();


    int val;
    if (map.get("orange", val)) {
        std::cout << "orange: " << val << "\n";
    }

    HashMap<int, int> map_int;
    map_int[1] = 2;
    map_int[2] = 4;
    map_int.print();


}
