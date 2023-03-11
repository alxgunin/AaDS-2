// dp[i][j] -- the maximum value of the last element of non-growing subsequence
// of first i element
#include <algorithm>
#include <iostream>
#include <vector>

long long FirstLess(std::vector<long long>& dp, long long val) {
  long long l = 0, r = dp.size();
  while (r - l > 1) {
    long long mid = (r + l) / 2;
    if (dp[mid] >= val) {
      l = mid;
    } else {
      r = mid;
    }
  }
  return r;
}

int main() {
  const long long kInf = 1e18;
  long long n;
  std::cin >> n;
  std::vector<long long> arr(n);
  for (long long& i : arr) {
    std::cin >> i;
  }
  std::vector<long long> dp(n + 1, -kInf);
  std::vector<long long> prev(n + 1, -1), index(n + 1, -1);
  dp[0] = kInf;
  for (long long i = 0; i < n; ++i) {
    long long pos = FirstLess(dp, arr[i]);
    if (pos <= n) {
      prev[i] = index[pos - 1];
      dp[pos] = arr[i];
      index[pos] = i;
    }
  }
  long long len = 0;
  for (long long i = n; i >= 1; --i) {
    if (dp[i] != -kInf) {
      len = i;
      break;
    }
  }
  std::cout << len << '\n';
  std::vector<long long> ans;
  long long pt = index[len];
  while (pt != -1) {
    ans.push_back(pt + 1);
    pt = prev[pt];
  }
  std::reverse(ans.begin(), ans.end());
  for (long long i : ans) {
    std::cout << i << ' ';
  }
  return 0;
}