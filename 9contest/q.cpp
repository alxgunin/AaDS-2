#include <algorithm>
#include <iostream>
#include <vector>
#include <set>

void fastios() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

typedef long long ll;
typedef std::pair<ll, ll> pii;
const ll INF = 1e18;

struct edge {
  ll from, to, f, c, w, paired;
  edge() = default;
  edge(int from, int to, int f, int c, int w): from(from), to(to), f(f), c(c), w(w) {}
  edge* other; 
};

class Graph {
private:
  ll n, m;
  std::vector<std::vector<edge>> g;
  std::vector<ll> d;
  std::vector<edge*> p;

public:
  void Input() {
    std::cin >> n >> m;
    g.resize(n);
    for (ll i = 0; i < m; ++i) {
      ll u, v, c, w;
      std::cin >> u >> v >> c >> w;
      --u;
      --v;
      edge e1(u, v, 0, c, w), e2(v, u, 0, 0, -w);
      e1.paired = g[v].size();
      e2.paired = g[u].size();
      g[u].push_back(e1);
      g[v].push_back(e2);
    }
    for (ll i = 0; i < n; ++i) {
      for (edge &e : g[i]) {
        e.other = &g[e.to][e.paired];
      }
    }
    d.resize(n);
    p.resize(n);
  }

  void Find(ll& cost) {
    while(1) {
      d.assign(n, INF);
      p.assign(n, nullptr);
      d[0] = 0;
      std::set<pii> s;
      for (ll i = 0; i < n; ++i) {
        s.insert(pii(d[i], i));
      }
      while(!s.empty()) {
        ll v = (*s.begin()).second;
        s.erase(s.begin());
        for (edge &e : g[v]) {
          if (e.f < e.c && d[e.to] > d[v] + e.w) {
            s.erase(pii(d[e.to], e.to));
            d[e.to] = d[v] + e.w;
            p[e.to] = &e;
            s.insert(pii(d[e.to], e.to));
          }
        }
      }
      if (d[n - 1] == INF) {
        break;
      }
      ll cur = n - 1;
      ll flow = INF;
      while(cur != 0) {
        edge* e = p[cur];
        flow = std::min(flow, e->c - e->f);
        cur = e->from;
      }
      cur = n - 1;
      while(cur != 0) {
        edge* e = p[cur];
        e->f += flow;
        e->other->f -= flow;
        cur = e->from;
      }
      cost += d[n - 1] * flow;
    }
  }
};

signed main() {
  fastios();
  Graph graph;
  graph.Input();
  ll cost = 0;
  graph.Find(cost);
  std::cout << cost << '\n';
  return 0;
}