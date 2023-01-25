#pragma once

#include <cstdio>

template<typename T>
class BinarySearchTree {
 public:
  [[nodiscard]] size_t size() const {
    return size_;
  }

  [[nodiscard]] bool empty() const {
    if (size_ == 0) {
      return true;
    } else {
      return false;
    }
  }

  bool contains(const T& value) {
    if (find(value) == nullptr) {
      return false;
    } else {
      return true;
    }
  }

  void insert(const T& value) {
    if (empty()) {
      ++size_;
      parent_ = new TreeNode(nullptr, nullptr, nullptr, value);
      return;
    }
    if (!contains(value)) {
      TreeNode* cur_node = parent_;
      TreeNode* prev_node = nullptr;
      while (cur_node != nullptr) {
        prev_node = cur_node;
        if (value < cur_node->value_) {
          cur_node = cur_node->left_;
        } else {
          cur_node = cur_node->right_;
        }
      }
      TreeNode* new_node = new TreeNode(nullptr, nullptr, prev_node, value);
      if (prev_node->value_ > value) {
        prev_node->left_ = new_node;
      } else {
        prev_node->right_ = new_node;
      }
      ++size_;
    }
  }

  void erase(const T& value) {
    TreeNode* node_to_delete = find(value);
    detach(node_to_delete);
    --size_;
  }

 private:
  struct TreeNode {
    TreeNode(TreeNode* left, TreeNode* right, TreeNode* parent, T value)
        : left_(left), right_(right), parent_(parent), value_(value) {};
    TreeNode* left_;
    TreeNode* right_;
    TreeNode* parent_;
    T value_;
  };

  TreeNode* parent_ = nullptr;
  size_t size_ = 0;

  TreeNode* find(const T& value) {
    TreeNode* cur_node = parent_;
    while (cur_node != nullptr && cur_node->value_ != value) {
      if (value < cur_node->value_) {
        cur_node = cur_node->left_;
      } else {
        cur_node = cur_node->right_;
      }
    }
    return cur_node;
  }

  void detach(TreeNode* node) {
    if (node->left_ == nullptr && node->right_ == nullptr) { // when node has no children
      if (node == parent_) {
        parent_ = nullptr;
        return;
      }
      if (node->parent_->left_ == node) {
        node->parent_->left_ = nullptr;
      } else {
        node->parent_->right_ = nullptr;
      }
      node->parent_ = nullptr;
    } else if (node->left_ != nullptr && node->right_ != nullptr) { // when node has two its children
      TreeNode* cur_node = node->right_;
      while (cur_node->left_ != nullptr) {
        cur_node = cur_node->left_;
      }
      TreeNode* new_node = new TreeNode(nullptr, nullptr, node->parent_, cur_node->value_);
      detach(cur_node);
      if (node->parent_->left_ == node) {
        node->parent_->left_ = new_node;
      } else {
        node->parent_->right_ = new_node;
      }
      node->left_->parent_ = new_node;
      node->right_->parent_ = new_node;
      new_node->left_ = node->left_;
      new_node->right_ = node->right_;
      node->right_ = nullptr;
      node->left_ = nullptr;
      node->parent_ = nullptr;
    } else { // when node has only one child
      TreeNode* not_null_node = (node->left_ != nullptr) ? node->left_ : node->right_;
      if (node->parent_->left_ == node) {
        node->parent_->left_ = not_null_node;
      } else {
        node->parent_->right_ = not_null_node;
      }
      not_null_node->parent_ = node->parent_;
      node->parent_ = nullptr;
      node->left_ = nullptr;
      node->right_ = nullptr;
    }
    delete node;
  }

};