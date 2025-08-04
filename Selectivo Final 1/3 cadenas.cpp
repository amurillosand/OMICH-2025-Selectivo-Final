#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int tt;
  cin >> tt;
  while (tt--) {

    string a, b, c;
    cin >> a >> b >> c;

    int na = int(a.size());
    int nb = int(b.size());

    vector<vector<int>> dp(na + 1, vector<int>(nb + 1, na + nb + 1));
    dp[0][0] = 0;
    for (int i = 0; i <= na; i++) {
      for (int j = 0; j <= nb; j++) {
        int k = i + j;
        if (i < na) {
          dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + int(a[i] != c[k]));
        }
        if (j < nb) {
          dp[i][j + 1] = min(dp[i][j + 1], dp[i][j] + int(b[j] != c[k]));
        }
      }
    }
    cout << dp[na][nb] << '\n';
  }

  return 0;
}