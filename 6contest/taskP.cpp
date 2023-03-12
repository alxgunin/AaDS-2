// dp[i][mask] -- number of ways to get
// to the i-th column with bitmask mask
#include <algorithm>
#include <iostream>
#include <vector>

typedef long long Ll;

const Ll kMod = 1e9 + 7;

int Prev(int mask, int first, int sz) {
  int res = first;
  for (int i = 0; i + 1 < sz; ++i) {
    int mask_bit1 = static_cast<int>(((1 << i) & mask) != 0);
    int mask_bit2 = static_cast<int>(((1 << (i + 1)) & mask) != 0);
    int res_bit1 = static_cast<int>(((1 << i) & res) != 0);
    int sum = mask_bit1 + mask_bit2 + res_bit1;
    if (sum > 2 || sum < 1) {
      return -1;
    }
    res += (1 << (i + 1)) * (2 - sum);
  }
  return res;
}

void Calc(int n, int m, const std::vector<std::vector<char>>& map,
          std::vector<std::vector<Ll>>& dp) {
  for (int mask = 0; mask < (1 << n); ++mask) {
    int bad = 0;
    for (int bit = 0; bit < n && bad == 0; ++bit) {
      if ((mask & (1 << bit)) != 0 && map[bit][0] == '-') {
        bad = 1;
      }
      if ((mask & (1 << bit)) == 0 && map[bit][0] == '+') {
        bad = 1;
      }
    }
    if (bad == 0) {
      dp[0][mask] = 1;
    }
  }
  for (int j = 1; j < m; ++j) {
    for (int mask = 0; mask < (1 << n); ++mask) {
      int bad = 0;
      for (int bit = 0; bit < n && bad == 0; ++bit) {
        if ((mask & (1 << bit)) != 0 && map[bit][j] == '-') {
          bad = 1;
        }
        if ((mask & (1 << bit)) == 0 && map[bit][j] == '+') {
          bad = 1;
        }
      }
      if (bad == 0) {
        int prev_mask = Prev(mask, 0, n);
        if (prev_mask != -1) {
          dp[j][mask] = (dp[j - 1][prev_mask] + dp[j][mask]) % kMod;
        }
        prev_mask = Prev(mask, 1, n);
        if (prev_mask != -1) {
          dp[j][mask] = (dp[j - 1][prev_mask] + dp[j][mask]) % kMod;
        }
      }
    }
  }
}

signed main() {
  int n, m;
  std::cin >> n >> m;
  std::vector<std::vector<char>> map(n, std::vector<char>(m));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      std::cin >> map[i][j];
    }
  }
  std::vector<std::vector<Ll>> dp(m, std::vector<Ll>(1 << n));
  Calc(n, m, map, dp);
  Ll ans = 0;
  for (int mask = 0; mask < (1 << n); ++mask) {
    ans = (ans + dp[m - 1][mask]) % kMod;
  }
  std::cout << ans << '\n';
}