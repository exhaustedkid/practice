#pragma once

#include <vector>
#include <cstdio>

template<typename T>
class Heap {
 public:
  Heap() {
    data_ = new T[capacity_];
  }
  explicit Heap(const std::vector<T>& values) {
    size_ = values.size();
    capacity_ = values.size() * 2;
    data_ = new T[capacity_];
    for (size_t i = 0; i < values.size(); ++i) {
      data_[i] = values[i];
    }
    for (int i = size_ / 2; i >= 0; --i) {
      sift(i);
    }
  }

  bool empty() {
    return size_ == 0;
  }

  void push(const T& value) {
    if (size_ == capacity_) {
      Reallocate();
    }
    ++size_;
    data_[size_ - 1] = value;
    size_t ind = size_ - 1;
    size_t parent = (ind - 1) >> 1;
    while (ind > 0 && data_[parent] > data_[ind]) {
      std::swap(data_[parent], data_[ind]);
      ind = parent;
      parent = (ind - 1) >> 1;
    }
  }

  void pop() {
    data_[0] = data_[size_ - 1];
    sift(0);
    --size_;
  }

  T min() {
    return data_[0];
  }

  ~Heap() {
    delete data_;
  }

 private:
  T* data_;
  size_t size_ = 0;
  size_t capacity_ = 8;

  void sift(size_t ind) {
    while ((ind << 1) + 2 < size_) {
      size_t left = (ind << 1) + 1;
      size_t right = (ind << 1) + 2;
      size_t min_son_index;
      data_[left] < data_[right] ? min_son_index = left : min_son_index = right;
      if (data_[ind] > data_[min_son_index]) {
        std::swap(data_[ind], data_[min_son_index]);
        ind = min_son_index;
      } else {
        break;
      }
    }
  }

  void Reallocate() {
    T* new_data = new T[capacity_ * 2];
    capacity_ *= 2;
    for (size_t i = 0; i < size_; ++i) {
      new_data[i] = data_[i];
    }
    delete data_;
    data_ = new_data;
  }
};