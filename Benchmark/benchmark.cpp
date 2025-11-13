#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "../Using_Container/HashMapContainer.hpp"
#include "../Using_Dynamic_Memory/HashMapDynamicMemory.hpp"

void benchmark_insert(size_t N) {
    std::vector<std::string> keys;
    for (size_t i = 0; i < N; ++i)
        keys.push_back("key" + std::to_string(i));

    // Benchmark HashMapA
    HashMapContainer<std::string, int> mapA;
    auto startA = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < N; ++i)
        mapA.insert(keys[i], i);
    auto endA = std::chrono::high_resolution_clock::now();
    std::cout << "HashMap Container insert time: "
              << std::chrono::duration<double>(endA - startA).count() << "s\n";

    // Benchmark HashMapB
    HashMapDynamicMemory<std::string, int> mapB;
    auto startB = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < N; ++i)
        mapB.insert(keys[i], i);
    auto endB = std::chrono::high_resolution_clock::now();
    std::cout << "HashMap Dynamic Memory insert time: "
              << std::chrono::duration<double>(endB - startB).count() << "s\n";

    // Benchmark HashMapB
    std::unordered_map<std::string, int> mapC;
    auto startC = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < N; ++i)
        mapC.insert(std::make_pair(keys[i], i));
    auto endC = std::chrono::high_resolution_clock::now();
    std::cout << "unordered_map insert time: "
              << std::chrono::duration<double>(endC - startC).count() << "s\n";

}



int main(){
    std::vector<int> ops_number{100, 1000, 10000, 100000, 1000000, 10000000};
    for (auto &ops: ops_number){
        std::cout<<"Number of operations: "<< ops << std::endl;
        benchmark_insert(ops);
    }
    return 0;

}
