#pragma once

#include <unordered_map>
#include <string>
#include <algorithm>
#include <optional>
#include <limits>

const int max_priority = std::numeric_limits<int>::max();

class lru_cache {
 public:
  explicit lru_cache(size_t max_size) : max_size_(max_size) {};

  std::optional<std::string> get(const std::string& name) {
    if (time_heap_.find(name) == time_heap_.end()) {
      return std::nullopt;
    }
    ++priority;
    time_heap_[name] = priority;
    if (priority == max_priority) {
      rehash();
    }
    return name;
  }

  void add(const std::string& name) {
    if (priority == max_priority) {
      rehash();
    }
    if (time_heap_.find(name) == time_heap_.end()) {
      if (cache_.size() > max_size_) {
        auto last_used = std::min_element(time_heap_.begin(), time_heap_.end());
        std::cout << "min el is " << last_used->first;
        auto cache_last_used = std::find(cache_.begin(), cache_.end(), last_used->first);
        cache_.erase(cache_last_used);
        time_heap_.erase(last_used);
      }
      ++priority;
      time_heap_.insert(std::make_pair(name, priority));
      cache_.push_back(name);
    } else {
      ++priority;
      time_heap_[name] = priority;
    }
  }

 private:
  size_t max_size_ = 1e9 + 7;
  size_t priority = 0;
  std::unordered_map<std::string, size_t> time_heap_;
  std::vector<std::string> cache_;

  void rehash() {
    for (auto& i: time_heap_) {
      i.second -= priority - time_heap_.size();
    }
  }
};