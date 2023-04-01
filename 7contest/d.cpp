#include <algorithm>
#include <iostream>
#include <vector>

std::vector<std::vector<int>> g, gt;
std::vector<int> used, topsort;

int color = 0;

void Dfs1(int v) {
  used[v] = 1;
  for (int u : g[v]) {
    if (used[u] == 0) {
      Dfs1(u);
    }
  }
  topsort.push_back(v);
}

void Dfs2(int v) {
  used[v] = color;
  for (int u : gt[v]) {
    if (used[u] == 0) {
      Dfs2(u);
    }
  }
}

signed main() {
  int n, m;
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
  for (int i = 0; i < n; ++i) {
    if (used[i] == 0) {
      Dfs1(i);
    }
  }
  used.assign(n, 0);
  std::reverse(topsort.begin(), topsort.end());
  for (int i : topsort) {
    if (used[i] == 0) {
      ++color;
      Dfs2(i);
    }
  }
  std::cout << color << '\n';
  for (int i : used) {
    std::cout << i << ' ';
  }
  return 0;
}