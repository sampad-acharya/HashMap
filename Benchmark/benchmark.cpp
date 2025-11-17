#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>
#include "../Using_Container/HashMapContainer.hpp"
#include "../Using_Dynamic_Memory/HashMapDynamicMemory.hpp"

const static size_t ELEMENTS_PER_BUCKET = 16;

// Utility: generate keys once
std::vector<std::string> generate_keys(size_t N) {
    std::vector<std::string> keys;
    keys.reserve(N);
    for (size_t i = 0; i < N; ++i)
        keys.push_back("key" + std::to_string(i));
    return keys;
}

// -------------------- Insert Benchmarks --------------------

void benchmark_insert_container(size_t N, const std::vector<std::string>& keys) {
    size_t bucket_size = N / ELEMENTS_PER_BUCKET;
    HashMapContainer<std::string, int> map{bucket_size};

    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < N; ++i)
        map.insert(keys[i], i);
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "HashMap Container insert time per op: "
              << std::chrono::duration<double>(end - start).count() / N << "s\n";
}

void benchmark_insert_dynamic(size_t N, const std::vector<std::string>& keys) {
    size_t bucket_size = N / ELEMENTS_PER_BUCKET;
    HashMapDynamicMemory<std::string, int> map{bucket_size};

    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < N; ++i)
        map.insert(keys[i], i);
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "HashMap Dynamic Memory insert time per op: "
              << std::chrono::duration<double>(end - start).count() / N << "s\n";
}

void benchmark_insert_unordered(size_t N, const std::vector<std::string>& keys) {
    std::unordered_map<std::string, int> map;

    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < N; ++i)
        map.insert(std::make_pair(keys[i], i));
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "unordered_map insert time per op: "
              << std::chrono::duration<double>(end - start).count() / N << "s\n";
}

// -------------------- Operator[] Benchmarks --------------------

void benchmark_operator_container(size_t N, const std::vector<std::string>& keys) {
    size_t bucket_size = N / ELEMENTS_PER_BUCKET;
    HashMapContainer<std::string, int> map{bucket_size};

    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < N; ++i)
        map[keys[i]] = i;
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "HashMap Container [] time per op: "
              << std::chrono::duration<double>(end - start).count() / N << "s\n";
}

void benchmark_operator_dynamic(size_t N, const std::vector<std::string>& keys) {
    size_t bucket_size = N / ELEMENTS_PER_BUCKET;
    HashMapDynamicMemory<std::string, int> map{bucket_size};

    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < N; ++i)
        map[keys[i]] = i;
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "HashMap Dynamic Memory [] time per op: "
              << std::chrono::duration<double>(end - start).count() / N << "s\n";
}

void benchmark_operator_unordered(size_t N, const std::vector<std::string>& keys) {
    std::unordered_map<std::string, int> map;

    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < N; ++i)
        map[keys[i]] = i;
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "unordered_map [] time per op: "
              << std::chrono::duration<double>(end - start).count() / N << "s\n";
}

// -------------------- Runner --------------------

void run_benchmark(void (*func)(size_t, const std::vector<std::string>&)) {
    std::vector<size_t> ops_number{100, 100000, 1000000};
    for (size_t ops : ops_number) {
        std::cout << "Number of operations: " << ops << "\n";
        auto keys = generate_keys(ops);
        func(ops, keys);
    }
}

int main() {
    try {
        std::cout << "\n=== Insert Benchmarks ===\n";
        run_benchmark(benchmark_insert_container);
        run_benchmark(benchmark_insert_dynamic);
        run_benchmark(benchmark_insert_unordered);

        std::cout << "\n=== Operator[] Benchmarks ===\n";
        run_benchmark(benchmark_operator_container);
        run_benchmark(benchmark_operator_dynamic);
        run_benchmark(benchmark_operator_unordered);
    }
    catch (const std::runtime_error& e) {
        std::cout << "Caught exception: " << e.what() << "\n";
    }

    std::cout << "Program exiting cleanly.\n";
    return 0;
}
