#pragma once
#include <utility>
#include <functional>
#include <stdexcept>
#include <iostream>

template<typename Key, typename Value>
class HashMapDynamicMemory{
private:
    static constexpr size_t DEFAULT_BUCKETS = 16;
    static constexpr size_t INITIAL_BUCKET_CAPACITY = 4;
    size_t bucket_size;
    size_t size;
    struct Bucket{
        public:
        std::pair<Key, Value> *entries;
        size_t count;
        size_t capacity;
        
        Bucket():count{0}, capacity{INITIAL_BUCKET_CAPACITY} {
            entries = new std::pair<Key, Value>[capacity];

        }

        ~Bucket(){
            delete []entries;
        }
        void resize(){
            size_t new_capacity = capacity == 0? 1 : 2 * capacity;
            std::pair<Key, Value> *new_entries = new std::pair<Key, Value>[new_capacity];
            for (int i = 0; i < count; ++i){
                new_entries[i] = entries[i];
            }
            delete []entries;

            entries = new_entries;
            capacity = new_capacity;

        }
    };

    Bucket **buckets;

public:
    
    HashMapDynamicMemory(size_t user_bucket_size) : bucket_size{user_bucket_size}, size{0}{
        buckets = new Bucket *[bucket_size];
        for (size_t i = 0; i < bucket_size; ++i){
            buckets[i] = new Bucket();
        }
    }
    HashMapDynamicMemory() : HashMapDynamicMemory(DEFAULT_BUCKETS) {};
    ~HashMapDynamicMemory(){
        for (int i = 0; i < bucket_size; ++i){
            delete buckets[i];
        }
        delete []buckets;

    }
    size_t hash(const Key &key) const{
        return std::hash<Key>{}(key) % bucket_size;
    }

    const Value & insert(const Key &key, const Value &value){
        size_t index = hash(key);
        auto &current_bucket = buckets[index];
        auto &bucket = current_bucket->entries;
        size_t bucket_length = current_bucket->count;
        size_t &current_capacity = current_bucket->capacity;
        for (int i = 0; i < bucket_length; ++i){
            if (key == bucket[i].first){
                bucket[i].second = value;
                return bucket[i].second;
            }
        }
        if (current_capacity == bucket_length){
            current_bucket->resize();
        }
        bucket[current_bucket->count++] = std::make_pair(key, value);
        ++size;
        return bucket[current_bucket->count - 1].second;
    }

    size_t count() const{
        return size;
    }

    bool get(const Key &key, Value &value) const{
        size_t index = hash(key);
        auto &current_bucket = buckets[index];
        auto &bucket = current_bucket->entries;
        size_t bucket_length = current_bucket->count;
        for (int i = 0; i < bucket_length; ++i){
            if (key == bucket[i].first){
                value = bucket[i].second;
                return true;
            }
        }
        return false;
    }

    bool erase(const Key &key){
        size_t index = hash(key);
        auto &current_bucket = buckets[index];
        auto &bucket = current_bucket->entries;
        size_t bucket_length = current_bucket->count;
        for (int i = 0; i < bucket_length; ++i){
            if (key == bucket[i].first){
                bucket[i] = std::move(bucket[bucket_length - 1]);
                --bucket_length;
                --size;
                return true;
            }
        }
        return false;
    }
    const Value & operator[](const Key &key) const{
        size_t index = hash(key);
        auto &current_bucket = buckets[index];
        auto &bucket = current_bucket->entries;
        size_t bucket_length = current_bucket->count;
        for (int i = 0; i < bucket_length; ++i){
            if (key == bucket[i].first){
                return bucket[i].second;
            }
        }
        throw std::out_of_range("Key is not found");
    }
    Value & operator[](const Key &key){
        size_t index = hash(key);
        auto &current_bucket = buckets[index];
        auto &bucket = current_bucket->entries;
        size_t bucket_length = current_bucket->count;
        size_t &current_capacity = current_bucket->capacity;
        for (int i = 0; i < bucket_length; ++i){
            if (key == bucket[i].first){
                return bucket[i].second;
            }
        }
        if (current_capacity == bucket_length){
            current_bucket->resize();
        }
        bucket[current_bucket->count++] = std::make_pair(key, Value{});
        ++size;    


        return bucket[current_bucket->count - 1].second;
    }
    
};