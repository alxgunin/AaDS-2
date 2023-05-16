#include <algorithm>
#include <iostream>
#include <vector>

typedef long long ll;

struct edge {
  ll from, to, cost;
};

bool cmp(const edge& a, const edge& b) {
  return a.cost < b.cost;
}

class Dsu {
public:
  std::vector<ll> p, rank;
  
  ll GetParent(ll x) {
    if (p[x] == -1) return x;
    return p[x] = GetParent(p[x]);
  }

  void Unite(ll x, ll y) {
    ll a = GetParent(x);
    ll b = GetParent(y);
    if (a == b) return;
    if (rank[a] < rank[b]) {
      std::swap(a, b);
    }
    if (rank[a] == rank[b]) {
      rank[a]++;
    }
    p[b] = a;
  }
};

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  ll n, m;
  std::cin >> n >> m;
  Dsu d;
  d.p.resize(n, -1);
  d.rank.resize(n);
  std::vector<edge> e;
  for (ll i = 0; i < m; ++i) {
    ll u, v, c;
    std::cin >> u >> v >> c;
    u--;
    v--;
    e.push_back(edge{u, v, c});
  }
  std::sort(e.begin(), e.end(), cmp);
  ll ans = 0;
  for (edge cur : e) {
    if (d.GetParent(cur.from) != d.GetParent(cur.to)) {
      d.Unite(cur.from, cur.to);
      ans += cur.cost;
    }
  }
  std::cout << ans << '\n';
  return 0;
}