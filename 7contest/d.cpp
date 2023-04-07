#include <algorithm>
#include <iostream>
#include <vector>

struct Graph {
  Graph() = default;

  int n, m;
  int color = 0;
  std::vector<std::vector<int>> g, gt;
  std::vector<int> used, topsort;

  void Dfs(int v) {
    used[v] = 1;
    for (int u : g[v]) {
      if (used[u] == 0) {
        Dfs(u);
      }
    }
    topsort.push_back(v);
  }

  void ShareColor(int v) {
    used[v] = color;
    for (int u : gt[v]) {
      if (used[u] == 0) {
        ShareColor(u);
      }
    }
  }

  void Input() {
    std::cin >> n >> m;
    g.resize(n);
    gt.resize(n);
    used.resize(n);
    for (int i = 0; i < m; ++i) {
      int u, v;
      std::cin >> u >> v;
      u--;
      v--;
      g[u].push_back(v);
      gt[v].push_back(u);
    }
  }

  void GetTopSort() {
    for (int i = 0; i < n; ++i) {
      if (used[i] == 0) {
        Dfs(i);
      }
    }
  }

  void Colorize() {
    used.assign(n, 0);
    std::reverse(topsort.begin(), topsort.end());
    for (int i : topsort) {
      if (used[i] == 0) {
        ++color;
        ShareColor(i);
      }
    }
  }
};

signed main() {
  Graph g;
  g.Input();
  g.GetTopSort();
  g.Colorize();
  std::cout << g.color << '\n';
  for (int i : g.used) {
    std::cout << i << ' ';
  }
  return 0;
}