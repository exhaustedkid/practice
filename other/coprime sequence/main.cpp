#include <iostream>
#include <vector>
#include <cmath>
#include <set>
#include <algorithm>

using namespace std;

typedef long long ll;

class Stack {
 public:
  vector<ll> s, gcd;
  bool empty() const {
    return s.empty();
  }
  void push(ll x) {
    s.push_back(x);
    gcd.push_back(gcd.empty() ? x : __gcd(gcd.back(), x));
  }
  ll pop() {
    ll res = s.back();
    s.pop_back();
    gcd.pop_back();
    return res;
  }
  ll _gcd() {
    return gcd.empty() ? 0 : gcd.back();
  }
};

Stack s1, s2;

void add(ll x) {
  s2.push(x);
}

ll remove() {
  if (s1.empty()) {
    while (!s2.empty()) {
      s1.push(s2.pop());
    }
  }
  return s1.pop();
}

bool thisgood() {
  if (s2.empty() && !s1.empty()) {
    return s1._gcd() == 1;
  }
  if (s1.empty() && !s2.empty()) {
    return s2._gcd() == 1;
  }
  if (!s1.empty() && !s2.empty()) {
    return __gcd(s1._gcd(), s2._gcd()) == 1;
  }
  return false;
}

bool nextgood() {
  ll cpy = remove();
  bool good = thisgood();
  s1.push(cpy);
  return good;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  long long n;
  cin >> n;
  vector<ll> a(n);
  for (auto i = 0; i < n; ++i) {
    cin >> a[i];
  }
  ll l = 0;
  ll res = LLONG_MAX;
  for (auto r = 0; r < n; ++r) {
    add(a[r]);
    while (nextgood()) {
      remove();
      ++l;
    }
    if (thisgood()) {
      res = min(res, r - l + 1);
    }
  }
  if (res == LLONG_MAX) {
    res = -1;
  }
  cout << res;
  return 0;
}