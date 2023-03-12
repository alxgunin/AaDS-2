// dp[i][j] -- maximum height using i planes and j experiements
#include <algorithm>
#include <iostream>
#include <vector>

int Calc(int i, int j, int** dp) {
  if (dp[i][j] == 0 && std::min(i, j) != 0) {
    if (i == 1) {
      dp[i][j] = j;
    } else {
      dp[i][j] = Calc(i, j - 1, dp) + Calc(i - 1, j - 1, dp) + 1;
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
  int** dp = new int*[30];
  for (int i = 0; i < 30; ++i) {
    dp[i] = new int[100'000]();
  }
  for (int j = 1; j < 100'000; ++j) {
    if (Calc(k, j, dp) >= n - 1) {
      std::cout << j << '\n';
      for (int i = 0; i < 30; ++i) {
        delete[] dp[i];
      }
      delete[] dp;
      return 0;
    }
  }
  for (int i = 0; i < 30; ++i) {
    delete[] dp[i];
  }
  delete[] dp;
  std::cout << -1 << '\n';
}