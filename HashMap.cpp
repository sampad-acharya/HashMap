#include "HashMap.hpp"

template<typename Key, typename Value>
size_t HashMap<Key, Value>::hash(const Key& key) const {
    return std::hash<Key>{}(key) % buckets.size();
}

template<typename Key, typename Value>
HashMap<Key, Value>::HashMap() : HashMap(DEFAULT_BUCKETS) {}

template<typename Key, typename Value>
HashMap<Key, Value>::HashMap(size_t bucket_size) : buckets(bucket_size), size(0) {}

template<typename Key, typename Value>
void HashMap<Key, Value>::insert(const Key& key, const Value& value) {
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

template<typename Key, typename Value>
bool HashMap<Key, Value>::get(const Key& key, Value& out) const {
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

template<typename Key, typename Value>
bool HashMap<Key, Value>::erase(const Key& key) {
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

template<typename Key, typename Value>
size_t HashMap<Key, Value>::count() const {
    return size;
}

template<typename Key, typename Value>
void HashMap<Key, Value>::print() const {
    for (size_t i = 0; i < buckets.size(); ++i) {
        std::cout << "Bucket " << i << ": ";
        for (const auto& kv : buckets[i]) {
            std::cout << "[" << kv.first << ": " << kv.second << "] ";
        }
        std::cout << "\n";
    }
}

template<typename Key, typename Value>
Value& HashMap<Key, Value>::operator[](const Key& key) {
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

template<typename Key, typename Value>
const Value& HashMap<Key, Value>::operator[](const Key& key) const {
    size_t index = hash(key);
    for (const auto& kv : buckets[index]) {
        if (kv.first == key) {
            return kv.second;
        }
    }
    throw std::out_of_range("Key is not found in the hashmap");
}

// Explicit template instantiation for common types
template class HashMap<std::string, int>;
template class HashMap<int, int>;
