#include <iostream>
#include <vector>
#include <cmath>
#include <set>
#include <algorithm>

using namespace std;

typedef long long ll;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  ll n, k;
  cin >> n >> k;
  vector<ll> a(n);
  ll max_of_array = 0;
  for (auto i = 0; i < n; ++i) {
    cin >> a[i];
    max_of_array = max(max_of_array, a[i]);
  }
  ll l = 0;
  ll r = 1e15;
  while (l + 1 < r) {
    ll m = (l + r) / 2;
    if (m < max_of_array) {
      l = m;
      continue;
    }
    ll count_of_particions = 0;
    ll cur_sum = 0;
    for (auto i = 0; i < n; ++i) {
      if (cur_sum + a[i] <= m) {
        cur_sum += a[i];
      } else {
        count_of_particions++;
        cur_sum = a[i];
      }
    }
    if (count_of_particions >= k) {
      l = m;
    } else {
      r = m;
    }
  }
  cout << r;
  return 0;
}