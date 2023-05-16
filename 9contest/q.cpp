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
  edge* other; 
};

class Graph {
public:
  ll n, m;
  std::vector<std::vector<edge>> g;
};

signed main() {
  fastios();
  Graph graph;
  std::cin >> graph.n >> graph.m;
  graph.g.resize(graph.n);
  for (ll i = 0; i < graph.m; ++i) {
    ll u, v, c, w;
    std::cin >> u >> v >> c >> w;
    u--;
    v--;
    edge e1, e2;
    e1.from = u;
    e1.to = v;
    e1.f = 0;
    e1.c = c;
    e1.w = w;
    e2.from = v;
    e2.to = u;
    e2.f = 0;
    e2.c = 0;
    e2.w = -w;
    e1.paired = graph.g[v].size();
    e2.paired = graph.g[u].size();
    graph.g[u].push_back(e1);
    graph.g[v].push_back(e2);
  }
  for (ll i = 0; i < graph.n; ++i) {
    for (edge &e : graph.g[i]) {
      e.other = &graph.g[e.to][e.paired];
    }
  }
  std::vector<ll> d(graph.n);
  std::vector<edge*> p(graph.n);
  ll cost = 0;
  while(1) {
    d.assign(graph.n, INF);
    p.assign(graph.n, nullptr);
    d[0] = 0;
    std::set<pii> s;
    for (ll i = 0; i < graph.n; ++i) {
      s.insert(pii(d[i], i));
    }
    while(!s.empty()) {
      ll v = (*s.begin()).second;
      s.erase(s.begin());
      for (edge &e : graph.g[v]) {
        if (e.f < e.c && d[e.to] > d[v] + e.w) {
          s.erase(pii(d[e.to], e.to));
          d[e.to] = d[v] + e.w;
          p[e.to] = &e;
          s.insert(pii(d[e.to], e.to));
        }
      }
    }
    if (d[graph.n - 1] == INF) {
      break;
    }
    ll cur = graph.n - 1;
    ll flow = INF;
    while(cur != 0) {
      edge* e = p[cur];
      flow = std::min(flow, e->c - e->f);
      cur = e->from;
    }
    cur = graph.n - 1;
    while(cur != 0) {
      edge* e = p[cur];
      e->f += flow;
      e->other->f -= flow;
      cur = e->from;
    }
    cost += d[graph.n - 1] * flow;
  }
  std::cout << cost << '\n';
  return 0;
}