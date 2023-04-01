#include <algorithm>
#include <iostream>
#include <vector>

struct Edge {
  int to, id;
  Edge(int to, int id) : to(to), id(id) {}
};

std::vector<std::vector<Edge>> g;
std::vector<int> used, h, d, ans;
const int kInf = 1e9;

void Dfs(int v, int id = -1) {
  used[v] = 1;
  d[v] = h[v];
  for (Edge e : g[v]) {
    if (used[e.to] == 0) {
      h[e.to] = h[v] + 1;
      Dfs(e.to, e.id);
      d[v] = std::min(d[e.to], d[v]);
    } else {
      if (e.id != id) {
        d[v] = std::min(d[v], h[e.to]);
      }
    }
  }
  if (d[v] > h[v] - 1 && id != -1) {
    ans.push_back(id);
  }
}

signed main() {
  int n, m;
  std::cin >> n >> m;
  g.resize(n);
  used.resize(n);
  d.resize(n, kInf);
  h.resize(n);
  for (int i = 0; i < m; ++i) {
    int u, v;
    std::cin >> u >> v;
    u--;
    v--;
    g[u].push_back(Edge(v, i));
    g[v].push_back(Edge(u, i));
  }
  for (int i = 0; i < n; ++i) {
    if (used[i] == 0) {
      h[i] = 1;
      Dfs(i);
    }
  }
  std::cout << ans.size() << '\n';
  sort(ans.begin(), ans.end());
  for (int i : ans) {
    std::cout << i + 1 << '\n';
  }
  return 0;
}