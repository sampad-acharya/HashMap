#pragma once
#include <vector>
#include <utility>
#include <functional>
#include <stdexcept>
#include <iostream>

template<typename Key, typename Value>
class HashMap {
private:
    static constexpr size_t DEFAULT_BUCKETS = 16;
    std::vector<std::vector<std::pair<Key, Value>>> buckets;
    size_t size;

    size_t hash(const Key& key) const;

public:
    HashMap();
    explicit HashMap(size_t bucket_size);

    void insert(const Key& key, const Value& value);
    bool get(const Key& key, Value& out) const;
    bool erase(const Key& key);
    size_t count() const;
    void print() const;

    Value& operator[](const Key& key);
    const Value& operator[](const Key& key) const;
};
