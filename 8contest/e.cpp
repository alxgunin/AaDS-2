#include <algorithm>
#include <iostream>
#include <vector>

using Pii = std::pair<int, int>;
const int kInf = 2009000999;
const int kMax = 100000;
const int kDefault = -1;

struct Edge {
  int to, val;
};

void Input(int& nn, std::vector<std::vector<Edge>>& gg) {
  std::cin >> nn;
  gg.resize(nn);
  for (int i = 0; i < nn; ++i) {
    for (int j = 0; j < nn; ++j) {
      int val;
      std::cin >> val;
      if (val != kMax) {
        gg[i].push_back(Edge{j, val});
      }
    }
  }
}

void Output(std::vector<int>& ans) {
  std::cout << "YES\n";
  std::cout << ans.size() << '\n';
  for (int vertex : ans) {
    std::cout << vertex + 1 << ' ';
  }
  std::cout << '\n';
}

void Output() { std::cout << "NO\n"; }

bool Solve(int nn, std::vector<std::vector<Edge>>& gg, std::vector<int>& ans) {
  std::vector<std::vector<int>> dp(nn, std::vector<int>(nn + 1, kInf));
  std::vector<int> pref(nn, -1);
  dp[0][0] = 0;
  int last = kDefault;
  for (int k = 1; k <= nn; ++k) {
    last = kDefault;
    for (int i = 0; i < nn; ++i) {
      dp[i][k] = dp[i][k - 1];
      for (auto& [prev, cost] : gg[i]) {
        if (dp[i][k] > dp[prev][k - 1] + cost) {
          last = i;
          dp[i][k] = dp[prev][k - 1] + cost;
          pref[i] = prev;
        }
      }
    }
  }
  if (last == kDefault) {
    return false;
  }
  for (int i = 0; i < nn; ++i) {
    last = pref[last];
  }
  int cur = last;
  do {
    ans.push_back(cur);
    cur = pref[cur];
  } while (cur != last);
  ans.push_back(ans[0]);
  return true;
}

signed main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  int nn;
  std::vector<std::vector<Edge>> gg;
  Input(nn, gg);
  std::vector<int> ans;
  if (Solve(nn, gg, ans)) {
    Output(ans);
  } else {
    Output();
  }
  return 0;
}