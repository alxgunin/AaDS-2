#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using Pii = std::pair<int, int>;
const int kInf = 2009000999;

void Solve() {
  int nn;
  int mm;
  std::cin >> nn >> mm;
  std::vector<std::vector<Pii>> gg(nn);
  for (int i = 0; i < mm; ++i) {
    int vv;
    int uu;
    int cc;
    std::cin >> vv >> uu >> cc;
    gg[vv].push_back(Pii{uu, cc});
    gg[uu].push_back(Pii{vv, cc});
  }
  int start = 0;
  std::cin >> start;
  std::vector<int> dist(nn, kInf);
  dist[start] = 0;
  std::set<Pii> ss;
  for (int i = 0; i < nn; ++i) {
    ss.insert(Pii(dist[i], i));
  }
  while (!ss.empty()) {
    int cur_dist = (*ss.begin()).first;
    int vv = (*ss.begin()).second;
    ss.erase(ss.begin());
    for (auto& [uu, cost] : gg[vv]) {
      if (dist[uu] > cur_dist + cost) {
        ss.erase(Pii(dist[uu], uu));
        dist[uu] = cur_dist + cost;
        ss.insert(Pii(dist[uu], uu));
      }
    }
  }
  for (int ii : dist) {
    std::cout << ii << ' ';
  }
  std::cout << '\n';
}

signed main() {
  int kk;
  std::cin >> kk;
  for (int i = 0; i < kk; ++i) {
    Solve();
  }
  return 0;
}