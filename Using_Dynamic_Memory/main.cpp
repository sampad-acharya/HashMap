#include <iostream>
#include <vector>
#include <utility>
#include <functional>
#include "HashMapDynamicMemory.hpp"


int main() {
    HashMap<std::string, int> map{10}; 
    map.insert("apple", 10);
    map.insert("banana", 20);
    map.insert("orange", 30); 
    int val;
    if (map.get("orange", val)) {
        std::cout << "orange: " << val << "\n";
    }

    std::cout << "Current size: "<< map.count() << "\n";
    map.erase("apple"); 
    std::cout << "Current size: "<< map.count() << "\n";
    map["mango"] = 10;
    std::cout << "mango: "<< map["fruit_new"] << "\n";

};
