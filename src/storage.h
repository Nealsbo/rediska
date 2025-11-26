#pragma once

#include <iostream>
#include <unordered_map>
#include <optional>
#include <memory>
#include <mutex>
#include <shared_mutex>

static const size_t initinal_map_size = 1031;

template <typename K = std::string, typename V = std::string>
class ThreadSafeMap {
public:
    ThreadSafeMap() {
        data.reserve(initinal_map_size);
    }

    ThreadSafeMap(int map_size) {
        data.reserve(map_size);
    }

    ~ThreadSafeMap() {
        std::unique_lock lock(sh_mutex);
        data.clear();
    }

    void Insert(const K& key, const V& value) {
        std::unique_lock lock(sh_mutex);
        data.insert(std::make_pair(key, value));
    }
    
    std::optional<V> FindOpt(const K& key) const {
        std::shared_lock slk(sh_mutex);
        auto it = data.find(key);
        if (it != data.end()) {
            return it->second;
        }
        return std::nullopt;
    }

    V Find(const K& key) const  {
        std::shared_lock slk(sh_mutex);
        auto it = data.find(key);
        if (it != data.end()) {
            return it->second;
        }
        return "";
    }

    void Delete(const K& key) {
        std::unique_lock lock(sh_mutex);
        auto it = data.find(key);
        if (it != data.end()) {
            data.erase(it);
        }
    }

    void Clear() {
        std::unique_lock lock(sh_mutex);
        data.clear();
    }

    bool IsEmpty() const {
        std::shared_lock lock(sh_mutex);
        return data.empty();
    }

    int Size() {
        std::shared_lock lock(sh_mutex);
        return data.size();
    }

    ThreadSafeMap& operator= (const ThreadSafeMap& t) = delete;

private:
    std::unordered_map<std::string, std::string> data;
    mutable std::shared_mutex sh_mutex;
};

class Storage {
public:
    Storage();
    ~Storage();

    void Init();

    void Insert(const std::string& key, const std::string& value);
    void Delete(const std::string& key);

    std::string Find(const std::string& key);
    
    void Clear();
    bool IsEmpty();
    
    void Shutdown();

private:
    bool shouldSaveData = false;
    std::unique_ptr<ThreadSafeMap<std::string, std::string>> storage_imp;
};