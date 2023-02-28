#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int k;
  cin >> k;
  string s;
  cin >> s;
  int ans = 0;
  for (char c = 'a'; c <= 'z'; ++c) {
    int k_copy = k;
    int r = 0;
    if (s[0] != c) {
      --k_copy;
    }
    for (auto l = 0; l < s.size(); ++l) {
      if (l != 0 && s[l - 1] != c) {
        ++k_copy;
      }
      while (k_copy >= 0 && r < s.size()) {
        ++r;
        if (r == s.size()) {
          ans = max(ans, r - l);
          break;
        }
        if (s[r] != c) {
          --k_copy;
        }
      }
      ans = max(ans, r - l);
    }
  }
  cout << ans;
  return 0;
}
