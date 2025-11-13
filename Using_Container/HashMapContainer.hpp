#pragma once
#include <vector>
#include <utility>
#include <functional>
#include <stdexcept>
#include <iostream>

template<typename Key, typename Value>
class HashMapContainer {
private:
    static constexpr size_t DEFAULT_BUCKETS = 16;
    std::vector<std::vector<std::pair<Key, Value>>> buckets;
    size_t size;

    size_t hash(const Key& key) const {
        return std::hash<Key>{}(key) % buckets.size();
    }

public:
    HashMapContainer() : HashMapContainer(DEFAULT_BUCKETS) {}
    explicit HashMapContainer(size_t bucket_size) : buckets(bucket_size), size(0) {}

    void insert(const Key& key, const Value& value) {
        size_t index = hash(key);
        auto& bucket = buckets[index];
        for (auto& kv : bucket) {
            if (kv.first == key) {
                kv.second = value;
                return;
            }
        }
        bucket.emplace_back(key, value);
        ++size;
    }

    bool get(const Key& key, Value& out) const {
        size_t index = hash(key);
        const auto& bucket = buckets[index];
        for (const auto& kv : bucket) {
            if (kv.first == key) {
                out = kv.second;
                return true;
            }
        }
        return false;
    }

    bool erase(const Key& key) {
        size_t index = hash(key);
        auto& bucket = buckets[index];
        for (size_t i = 0; i < bucket.size(); ++i) {
            if (bucket[i].first == key) {
                bucket[i] = std::move(bucket.back());
                bucket.pop_back();
                --size;
                return true;
            }
        }
        return false;
    }

    size_t count() const {
        return size;
    }

    void print() const {
        for (size_t i = 0; i < buckets.size(); ++i) {
            std::cout << "Bucket " << i << ": ";
            for (const auto& kv : buckets[i]) {
                std::cout << "[" << kv.first << ": " << kv.second << "] ";
            }
            std::cout << "\n";
        }
    }

    Value& operator[](const Key& key) {
        size_t index = hash(key);
        for (auto& kv : buckets[index]) {
            if (kv.first == key) {
                return kv.second;
            }
        }
        buckets[index].emplace_back(key, Value{});
        ++size;
        return buckets[index].back().second;
    }

    const Value& operator[](const Key& key) const {
        size_t index = hash(key);
        for (const auto& kv : buckets[index]) {
            if (kv.first == key) {
                return kv.second;
            }
        }
        throw std::out_of_range("Key is not found in the hashmap");
    }
};
