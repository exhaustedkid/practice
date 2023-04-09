#include <iostream>
#include <vector>

using namespace std;

int main() {
  string s;
  cin >> s;
  int n = s.size();
  vector<int> z(n);
  int l = 0, r = 0;
  for (auto i = 1; i < n; ++i) {
    if (r >= i) {
      z[i] = min(z[i - l], r - i + 1);
    }
    while (i + z[i] < n && s[z[i]] == s[z[i] + i]) {
      ++z[i];
    }
    if (i + z[i] - 1 > r) {
      l = i;
      r = i + z[i] - 1;
    }
  }
  return 0;
}
