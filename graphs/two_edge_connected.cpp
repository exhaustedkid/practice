#include <iostream>
#include <vector>
#include <cmath>
#include <set>
#include <algorithm>

using namespace std;

vector<int> graph[100000];
vector<int> tree[100000];
int used[100000];
int comp[100000];
int tin[100000];
int fup[100000];
int timer;
vector<pair<int, int>> deleted_edges;
vector<pair<int, int>> bridges;

void dfs(int v, int p = -1) {
  used[v] = true;
  tin[v] = fup[v] = timer++;
  for (size_t i = 0; i < graph[v].size(); ++i) {
    int to = graph[v][i];
    if (to == p) continue;
    if (used[to])
      fup[v] = min(fup[v], tin[to]);
    else {
      dfs(to, v);
      fup[v] = min(fup[v], fup[to]);
      if (fup[to] > tin[v])
        bridges.emplace_back(v, to);
    }
  }
}

void find_bridges(int n) {
  timer = 0;
  for (int i = 0; i < n; ++i)
    used[i] = false;
  for (int i = 0; i < n; ++i)
    if (!used[i])
      dfs(i);
}

void find_component(int v, int cur_comp_num) {
  used[v] = true;
  comp[v] = cur_comp_num;
  for (int u: graph[v]) {
    if (!used[u]) {
      find_component(u, cur_comp_num);
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  int m;
  cin >> n >> m;
  for (auto i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }
  find_bridges(n);
  for (auto& bridge: bridges) { // delete bridges from G
    auto it = find(graph[bridge.first].begin(), graph[bridge.first].end(), bridge.second);
    graph[bridge.first].erase(it);
    deleted_edges.emplace_back(make_pair(bridge.first, bridge.second));
  }
  for (auto& bridge: bridges) {
    auto it = find(graph[bridge.second].begin(), graph[bridge.second].end(), bridge.first);
    graph[bridge.second].erase(it);
  }
  for (auto i = 0; i < n; ++i) {
    used[i] = false;
  }
  int c_num = 0;
  for (int i = 0; i < n; i++) { // partice vertices on connectivity components
    if (!used[i]) {
      find_component(i, c_num);
      c_num++;
    }
  }
  c_num--;
  for (auto j: deleted_edges) { // create G_c
    tree[comp[j.first]].push_back(comp[j.second]);
    tree[comp[j.second]].push_back(comp[j.first]);
  }

  vector<int> vertices_ged_1; // find hanging vertices in G_c
  for (auto i = 0; i <= c_num; ++i) {
    if (tree[i].size() == 1) {
      vertices_ged_1.push_back(i);
    }
  }

  int added_edge_begin; // out added edges
  int added_edge_end;
  if (vertices_ged_1.size() % 2 == 0) {
    for (auto i = 0; i < vertices_ged_1.size(); i += 2) {
      for (auto j = 0; j < n; ++j) {
        if (comp[j] == vertices_ged_1[i]) {
          added_edge_begin = j;
        }
        if (comp[j] == vertices_ged_1[i + 1]) {
          added_edge_end = j;
        }
      }
      cout << added_edge_begin + 1 << ' ' << added_edge_end + 1 << '\n';
    }
  } else {
    for (auto i = 0; i < vertices_ged_1.size() - 1; i += 2) {
      for (auto j = 0; j < n; ++j) {
        if (comp[j] == vertices_ged_1[i]) {
          added_edge_begin = j;
        }
        if (comp[j] == vertices_ged_1[i + 1]) {
          added_edge_end = j;
        }
      }
      cout << added_edge_begin + 1 << ' ' << added_edge_end + 1 << '\n';
    }
    for (auto j = 0; j < n; ++j) {
      if (comp[j] == vertices_ged_1[vertices_ged_1.size() - 1]) {
        added_edge_begin = j;
      }
      if (comp[j] == vertices_ged_1[0]) {
        added_edge_end = j;
      }
    }
    cout << added_edge_begin + 1 << ' ' << added_edge_end + 1 << '\n';
  }
  return 0;
}
