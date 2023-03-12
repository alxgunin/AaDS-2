// dp[i][j][k] -- maximum quantity of common symbols between
// some prefix a length i after q addings and j erases
// and string b
#include <algorithm>
#include <iostream>
#include <vector>

std::vector<std::vector<std::vector<int>>> Calc(int n, int k, int m, std::string& a, std::string& b) {
  std::vector<std::vector<std::vector<int>>> dp(m + 1, std::vector<std::vector<int>>(k + 1, std::vector<int>(k + 1)));
  for (int i = 1; i <= m; ++i) {
    for (int j = 0; j <= std::min(n, k); ++j) {
      for (int q = 0; q <= std::min(k - j, i); ++q) {
        if (j > 0) {
          dp[i][j][q] = std::max(dp[i][j][q], dp[i][j - 1][q]);
        }
        if (q > 0) {
          dp[i][j][q] = std::max(dp[i][j][q], dp[i - 1][j][q - 1] + 1);
        }
        if (i + j - q > 0 && i + j - q - 1 < n) {
          dp[i][j][q] = std::max(dp[i][j][q], dp[i - 1][j][q] + static_cast<int>(a[i + j - q - 1] == b[i - 1]));
        }
      }
    }
  }
  return dp;
}

signed main() {
  std::string a, b;
  std::cin >> a >> b;
  int n = a.size(), m = b.size(), k;
  std::cin >> k;
  if (std::abs(n - m) > k) {
    std::cout << -1 << '\n';
    return 0;
  }
  std::vector<std::vector<std::vector<int>>> dp = Calc(n, k, m, a, b);
  int ans = 0;
  for (int j = 0; j <= k; ++j) {
    for (int q = 0; q <= k; ++q) {
      if (n - j + q == m) {
        ans = std::max(ans, dp[m][j][q] + std::max(0, k - q - j));
      }
    }
  }
  std::cout << std::max(0, m - ans) << '\n';
  return 0;
}