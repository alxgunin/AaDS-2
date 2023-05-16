#include <algorithm>
#include <iostream>
#include <vector>

void fastios() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

typedef long long ll;

class Graph {
public:
  std::vector<std::vector<ll>> g1, g2;
  std::vector<ll> used1, used2;
  void dfs(ll v, ll part) {
    if (part == 0) {
      used1[v] = 1;
      for (ll i : g1[v]) {
        if (!used2[i]) {
          dfs(i, part ^ 1);
        }
      }
    } else {
      used2[v] = 1;
      for (ll i : g2[v]) {
        if (!used1[i]) {
          dfs(i, part ^ 1);
        }
      }
    }
  }
};

signed main() {
  fastios();
  ll n, m;
  std::cin >> m >> n;
  Graph g;
  g.g1.resize(m);
  g.g2.resize(n);
  g.used1.resize(m);
  g.used2.resize(n);
  for (ll i = 0; i < m; ++i) {
    ll sz;
    std::cin >> sz;
    for (ll j = 0; j < sz; ++j) {
      ll vertex;
      std::cin >> vertex;
      g.g1[i].push_back(vertex - 1);
    }
  }
  for (ll i = 0; i < m; ++i) {
    ll pair;
    std::cin >> pair;
    pair--;
    for (auto it = g.g1[i].begin(); it != g.g1[i].end(); ++it) {
      if (*it == pair) {
        g.g2[pair].push_back(i);
        g.g1[i].erase(it);
        break;
      }
    }
  }
  std::vector<ll> cnt_in(m);
  for (ll i = 0; i < n; ++i) {
    for (ll to : g.g2[i]) {
      cnt_in[to]++;
    }
  }
  for (ll i = 0; i < m; ++i) {
    if (cnt_in[i] == 0) {
      g.dfs(i, 0);
    }
  }
  std::vector<ll> l, r;
  for (ll i = 0; i < m; ++i) {
    if (!g.used1[i]) {
      l.push_back(i + 1);
    }
  }
  for (ll i = 0; i < n; ++i) {
    if (g.used2[i]) {
      r.push_back(i + 1);
    }
  }
  ll ans = l.size() + r.size();
  std::cout << ans << '\n' << l.size() << ' ';
  for (ll i : l) std::cout << i << ' ';
  std::cout << '\n' << r.size() << ' ';
  for (ll i : r) std::cout << i << ' ';
  return 0;
}