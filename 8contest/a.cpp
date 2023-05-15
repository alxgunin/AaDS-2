#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

struct Edge {
  int to, cost;
};

using Pii = std::pair<int, int>;
const int kInf = 2009000999;

struct Elem {
  int dist, vertex;
};

bool operator<(const Elem& aa, const Elem& bb) {
  return (aa.dist < bb.dist) || (aa.dist == bb.dist && aa.vertex < bb.vertex);
}

std::vector<int> Solve(int nn, std::vector<std::vector<Edge>>& gg) {
  int start = 0;
  std::cin >> start;
  std::vector<int> dist(nn, kInf);
  dist[start] = 0;
  std::set<Elem> ss;
  for (int i = 0; i < nn; ++i) {
    ss.insert(Elem{dist[i], i});
  }
  while (!ss.empty()) {
    int cur_dist = (*ss.begin()).dist;
    int vv = (*ss.begin()).vertex;
    ss.erase(ss.begin());
    for (Edge& ee : gg[vv]) {
      int uu = ee.to;
      int cost = ee.cost;
      if (dist[uu] > cur_dist + cost) {
        ss.erase(Elem{dist[uu], uu});
        dist[uu] = cur_dist + cost;
        ss.insert(Elem{dist[uu], uu});
      }
    }
  }
  return dist;
}

void Input(int& nn, int& mm, std::vector<std::vector<Edge>>& gg) {
  std::cin >> nn >> mm;
  gg.resize(nn);
  for (int i = 0; i < mm; ++i) {
    int vv;
    int uu;
    int cc;
    std::cin >> vv >> uu >> cc;
    gg[vv].push_back(Edge{uu, cc});
    gg[uu].push_back(Edge{vv, cc});
  }
}

void Output(std::vector<int>& dist) {
  for (int ii : dist) {
    std::cout << ii << ' ';
  }
  std::cout << '\n';
}

signed main() {
  int kk;
  std::cin >> kk;
  for (int i = 0; i < kk; ++i) {
    int nn;
    int mm;
    std::vector<std::vector<Edge>> gg;
    Input(nn, mm, gg);
    std::vector<int> dist = Solve(nn, gg);
    Output(dist);
  }
  return 0;
}