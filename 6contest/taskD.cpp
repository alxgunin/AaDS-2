// dp[i][j] -- maximum height using i planes and j experiements
#include <algorithm>
#include <iostream>
#include <vector>

int dp[1'000][100'000];

int Calc(int i, int j) {
  if (dp[i][j] == 0 && std::min(i, j) != 0) {
    if (i == 1) {
      dp[i][j] = j;
    } else {
      dp[i][j] = Calc(i, j - 1) + Calc(i - 1, j - 1) + 1;
    }
  }
  return dp[i][j];
}

int main() {
  int n, k;
  std::cin >> n >> k;
  int p = 1;
  int cnt = 0;
  while (p < n) {
    p *= 2;
    cnt++;
  }
  if (cnt <= k) {
    std::cout << cnt << '\n';
    return 0;
  }
  for (int j = 1; j < 100'000; ++j) {
    if (Calc(k, j) >= n - 1) {
      std::cout << j << '\n';
      return 0;
    }
  }
  std::cout << -1 << '\n';
}