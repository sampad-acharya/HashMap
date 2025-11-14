#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>
//#include "absl/container/flat_hash_map.h"
#include "../Using_Container/HashMapContainer.hpp"
#include "../Using_Dynamic_Memory/HashMapDynamicMemory.hpp"

const static size_t ELEMENTS_PER_BUCKET = 16;

void benchmark_insert(size_t N) {
    std::vector<std::string> keys;
    size_t bucket_size = N / ELEMENTS_PER_BUCKET;
    for (size_t i = 0; i < N; ++i)
        keys.push_back("key" + std::to_string(i));

    // Benchmark HashMapA
    HashMapContainer<std::string, int> mapA{bucket_size};
    auto startA = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < N; ++i)
        mapA.insert(keys[i], i);
    auto endA = std::chrono::high_resolution_clock::now();
    std::cout << "HashMap Container insert time per operation: "
              << std::chrono::duration<double>(endA - startA).count() / N<< "s\n";

    // Benchmark HashMapB
    HashMapDynamicMemory<std::string, int> mapB{bucket_size};
    auto startB = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < N; ++i)
        mapB.insert(keys[i], i);
    auto endB = std::chrono::high_resolution_clock::now();
    std::cout << "HashMap Dynamic Memory insert time per operation: "
              << std::chrono::duration<double>(endB - startB).count() / N << "s\n";

    // Benchmark HashMapB
    std::unordered_map<std::string, int> mapC;
    auto startC = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < N; ++i)
        mapC.insert(std::make_pair(keys[i], i));
    auto endC = std::chrono::high_resolution_clock::now();
    std::cout << "unordered_map insert time per operation: "
              << std::chrono::duration<double>(endC - startC).count() / N << "s\n";

}


void benchmark_insert_operator(size_t N) {
    std::vector<std::string> keys;
    size_t bucket_size = N / ELEMENTS_PER_BUCKET;
    for (size_t i = 0; i < N; ++i)
        keys.push_back("key" + std::to_string(i));

    // Benchmark HashMapA
    HashMapContainer<std::string, int> mapA{bucket_size};
    auto startA = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < N; ++i)
        mapA[keys[i]] = i;
    auto endA = std::chrono::high_resolution_clock::now();
    std::cout << "HashMap Container [] operator time per operation: "
              << std::chrono::duration<double>(endA - startA).count() / N << "s\n";

    // Benchmark HashMapB
    HashMapDynamicMemory<std::string, int> mapB{bucket_size};
    auto startB = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < N; ++i)
        mapB[keys[i]] = i;
    auto endB = std::chrono::high_resolution_clock::now();
    std::cout << "HashMap Dynamic Memory [] operator time per operation: "
              << std::chrono::duration<double>(endB - startB).count() / N << "s\n";

    // Benchmark HashMapB
    std::unordered_map<std::string, int> mapC;
    auto startC = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < N; ++i)
        mapC[keys[i]] = i;
    auto endC = std::chrono::high_resolution_clock::now();
    std::cout << "unordered_map [] operator time per operation: "
              << std::chrono::duration<double>(endC - startC).count() / N<< "s\n";

}
void run_benchmark(void (*func)(size_t)){
    std::vector<size_t> ops_number{100, 100000, 10000000, 100000000};
    for (size_t &ops: ops_number){
        std::cout<<"Number of operations: "<< ops << std::endl;
        func(ops);
    }
}


int main() {
    try {
        run_benchmark(benchmark_insert_operator);
        run_benchmark(benchmark_insert);
    }
    catch (const std::runtime_error& e) {
        std::cout << "Caught exception: " << e.what() << "\n";
    }

    std::cout << "Program exiting cleanly.\n";
    return 0;
}
