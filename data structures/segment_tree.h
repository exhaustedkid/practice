#include <vector>

class SegmentTree {
 public:
  explicit SegmentTree(const std::vector<long long>& a) {
    size_ = 1;
    while (size_ < a.size()) size_ *= 2;
    tree_.assign(2 * size_ - 1, 0);
    build(0, 0, size_, a);
  }

  long long sum(int l, int r) {
    return get_sum(l, r, 0, 0, size_);
  }

  void modify(int ind, int val) {
    modify(ind, val, 0, 0, size_);
  }

 private:
  int size_ = 0;
  std::vector<long long> tree_;

  void build(int v, int tl, int tr, const std::vector<long long>& a) {
    if (tr - tl == 1) {
      if (tl < a.size()) tree_[v] = a[tl];
      return;
    }
    int m = (tl + tr) / 2;
    build(2 * v + 1, tl, m, a);
    build(2 * v + 2, m, tr, a);
    tree_[v] = tree_[2 * v + 1] + tree_[2 * v + 2];
  }

  long long get_sum(int l, int r, int v, int tl, int tr) {
    if (l <= tl && tr <= r) {
      return tree_[v];
    }
    if (tr <= l || r <= tl) {
      return 0;
    }
    int m = (tl + tr) / 2;
    return get_sum(l, r, 2 * v + 1, tl, m)
        + get_sum(l, r, 2 * v + 2, m, tr);
  }

  void modify(int ind, int val, int v, int tl, int tr) {
    if (tr - tl == 1) {
      tree_[v] = val;
      return;
    }
    int m = (tl + tr) / 2;
    if (ind < m) {
      modify(ind, val, 2 * v + 1, tl, m);
    } else {
      modify(ind, val, 2 * v + 2, m, tr);
    }
    tree_[v] = tree_[2 * v + 1] + tree_[2 * v + 2];
  }
};
