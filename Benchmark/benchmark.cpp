#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include "HashMapContainer.hpp"
#include "HashMapDynamicMemory.hpp"

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
    std::cout << "HashMapContainer insert time: "
              << std::chrono::duration<double>(endA - startA).count() << "s\n";

    // Benchmark HashMapB
    HashMapDynamicMemory<std::string, int> mapB;
    auto startB = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < N; ++i)
        mapB.insert(keys[i], i);
    auto endB = std::chrono::high_resolution_clock::now();
    std::cout << "HashMapDynamicMemory insert time: "
              << std::chrono::duration<double>(endB - startB).count() << "s\n";
}



int main(){
    std::vector<int> ops_number{100, 1000, 10000, 100000, 1000000, 10000000};
    for (auto &ops: ops_number){
        std::cout<<"Number of operations: "<< ops << std::endl;
        for (int trial = 0; trial < 5; ++trial)
        benchmark_insert(ops);
    }
    return 0;

}
