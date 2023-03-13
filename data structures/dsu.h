#include <vector>

#pragma once

class dsu {
 public:
  explicit dsu(int size) {
    for (auto i = 1; i <= size; ++i) {
      parent_.push_back(i);
      size_.push_back(1);
    }
  }

  explicit dsu(const std::vector<int>& v) {
    for (auto val: v) {
      parent_.push_back(val);
      size_.push_back(1);
    }
  }

  int FindSet(int x) {
    if (parent_[x] == x) {
      return x;
    }
    int new_parent = FindSet(parent_[x]);
    parent_[x] = new_parent;
    return new_parent;
  }

  void Union(int x, int y) {
    int root_x = FindSet(x);
    int root_y = FindSet(y);
    if (root_x == root_y) return;
    if (size_[root_x] < size_[root_y] || size_[root_x] == size_[root_y]) {
      parent_[root_x] = root_y;
      size_[root_y] += size_[root_x];
    } else {
      parent_[root_y] = root_x;
      size_[root_x] += size_[root_y];
    }
  }

 private:
  std::vector<int> parent_ = {-1};
  std::vector<int> size_ = {-1};
};
