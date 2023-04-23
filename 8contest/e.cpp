#include <algorithm>
#include <iostream>
#include <vector>

using Pii = std::pair<int, int>;
const int kInf = 2009000999;
const int kMax = 100000;
const int kDefault = -1;

void Solve() {
  int nn;
  std::cin >> nn;
  std::vector<std::vector<Pii>> gg(nn);
  for (int i = 0; i < nn; ++i) {
    for (int j = 0; j < nn; ++j) {
      int val;
      std::cin >> val;
      if (val != kMax) {
        gg[i].push_back(Pii(j, val));
      }
    }
  }

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
    std::cout << "NO\n";
    return;
  }
  std::cout << "YES\n";
  for (int i = 0; i < nn; ++i) {
    last = pref[last];
  }
  std::vector<int> ans;
  int cur = last;
  do {
    ans.push_back(cur);
    cur = pref[cur];
  } while (cur != last);
  ans.push_back(ans[0]);
  std::cout << ans.size() << '\n';
  for (int vertex : ans) {
    std::cout << vertex + 1 << ' ';
  }
  std::cout << '\n';
}

signed main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  Solve();
  return 0;
}