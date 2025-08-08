#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6 + 1;
unordered_map<int, long long> dp;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  long long idx = 1;
  for (int row = 1; idx <= MAXN; ++row) {
    for (int pos = 1; pos <= row; ++pos) {
      idx = (row * (row - 1) / 2) + pos;
      if (idx > MAXN)
        break;

      long long sq = idx * idx;

      if (row == 1 && pos == 1) {
        dp[idx] = sq;
      } else if (pos == 1) {
        // Left edge
        dp[idx] = sq + dp[((row - 1) * (row - 2) / 2) + pos];
      } else if (pos == row) {
        // Right edge
        dp[idx] = sq + dp[((row - 1) * (row - 2) / 2) + (pos - 1)];
      } else {
        // Middle
        long long parent1 = ((row - 1) * (row - 2) / 2) + (pos - 1);
        long long parent2 = ((row - 1) * (row - 2) / 2) + pos;
        long long grandparent = ((row - 2) * (row - 3) / 2) + (pos - 1);
        dp[idx] = sq + dp[parent1] + dp[parent2] - dp[grandparent];
      }
    }
  }

  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    cout << dp[n] << '\n';
  }
  return 0;
}
