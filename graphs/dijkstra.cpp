#include <iostream>
#include <vector>
#include <queue>

typedef long long ll;
using namespace std;

vector<pair<int, int>> graph[200000];
ll dist[200000];
bool used[200000];
ll inf = INT64_MAX;

int main() {
  int n;
  cin >> n;
  int m;
  cin >> m;
  for (auto i = 0; i < m; ++i) {
    int u, v, w;
    cin >> u >> v >> w;
    --u, --v;
    graph[u].emplace_back(v, w);
    graph[v].emplace_back(u, w);
  }
  for (auto i = 0; i < n; ++i) {
    dist[i] = inf;
  }
  priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> q;
  q.push({0, 0});
  dist[0] = 0;
  while (!q.empty()) {
    int u = q.top().second;
    q.pop();
    if (used[u]) continue;
    used[u] = true;
    for (auto v : graph[u]) {
        if (dist[v.first] > dist[u] + v.second) {
          dist[v.first] = dist[u] + v.second;
          q.push({dist[v.first], v.first});
        }
    }
  }
  cout << dist[n - 1];
  return 0;
}
