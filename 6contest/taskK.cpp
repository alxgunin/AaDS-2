// dp[i][j] -- maximum cost on first i elements with weight j
#include <algorithm>
#include <iostream>
#include <vector>

std::vector<int> GetAnswer(int n, int m, std::vector<std::vector<int>>& dp,
                           std::vector<int>& w, std::vector<int>& c) {
  std::vector<int> ans;
  int mx = -1;
  int weight = -1;
  for (int i = 0; i <= m; ++i) {
    if (dp[n][i] >= mx) {
      mx = dp[n][i];
      weight = i;
    }
  }
  for (int i = n - 1; i >= 0; --i) {
    for (int j = 0; j <= m; ++j) {
      if (dp[i + 1][weight] == dp[i][weight]) {
        break;
      }
      if (dp[i + 1][weight] == dp[i][weight - w[i + 1]] + c[i + 1]) {
        weight -= w[i + 1];
        ans.push_back(i + 1);
        break;
      }
    }
  }
  std::reverse(ans.begin(), ans.end());
  return ans;
}

void Calc(int n, int m, std::vector<std::vector<int>>& dp, std::vector<int>& w,
          std::vector<int>& c) {
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j <= m; ++j) {
      dp[i][j] = dp[i - 1][j];
      if (j >= w[i]) {
        dp[i][j] = std::max(dp[i][j], dp[i - 1][j - w[i]] + c[i]);
      }
    }
  }
}

int main() {
  int n, m;
  std::cin >> n >> m;
  std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1));
  std::vector<int> w(n + 1), c(n + 1);
  for (int i = 1; i <= n; ++i) {
    std::cin >> w[i];
  }
  for (int i = 1; i <= n; ++i) {
    std::cin >> c[i];
  }
  Calc(n, m, dp, w, c);
  std::vector<int> ans = GetAnswer(n, m, dp, w, c);
  for (int& i : ans) {
    std::cout << i << '\n';
  }
}