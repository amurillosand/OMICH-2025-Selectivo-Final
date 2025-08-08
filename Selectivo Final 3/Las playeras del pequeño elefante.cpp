#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int N = 101;

void add(int& a, int b) {
  a += b;
  if (a >= MOD)
    a -= MOD;
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    cin.ignore();

    vector<vector<int>> owners(N);
    string line;
    for (int i = 0; i < n; ++i) {
      getline(cin, line);
      istringstream ss(line);
      int id;
      while (ss >> id) {
        owners[id].push_back(i);
      }
    }

    int fullMask = (1 << n) - 1;
    vector<int> dp(1 << n, 0), ndp;
    dp[0] = 1;

    for (int s = 1; s < N; ++s) {
      ndp = dp;
      for (int mask = 0; mask <= fullMask; ++mask) {
        if (dp[mask] == 0)
          continue;
        for (int i : owners[s]) {
          if (!(mask & (1 << i))) {
            int newMask = mask | (1 << i);
            add(ndp[newMask], dp[mask]);
          }
        }
      }
      swap(dp, ndp);
    }

    cout << dp[fullMask] << '\n';
  }

  return 0;
}
