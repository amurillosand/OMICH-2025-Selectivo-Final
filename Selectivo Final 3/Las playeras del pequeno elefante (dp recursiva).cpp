#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int N = 100;

void add(int& a, int b) {
  a += b;
  if (a >= MOD)
    a -= MOD;
};

vector<int> owners[N + 1];
int mem[N + 1][1 << 10];
int done[N + 1][1 << 10];
int timer = 0;
int n;

int dp(int p, int mask) {
  if (p > N) {
    // todos tiene playera
    return (mask == (1 << n) - 1);
  }

  int& ans = mem[p][mask];
  if (done[p][mask] != timer) {
    done[p][mask] = timer;
    ans = 0;

    // no tomar playera p
    ans = dp(p + 1, mask);

    // tomar playera p
    for (int i : owners[p]) {
      // si i todavia no tiene playera
      if (!(mask & (1 << i))) {
        add(ans, dp(p + 1, mask | (1 << i)));
      }
    }
  }

  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;
  while (t--) {
    cin >> n;
    cin.ignore();

    for (int i = 1; i <= N; ++i) {
      owners[i].clear();
    }

    string line;
    for (int i = 0; i < n; ++i) {
      getline(cin, line);
      istringstream ss(line);
      int id;
      while (ss >> id) {
        owners[id].push_back(i);
      }
    }

    ++timer;
    cout << dp(0, 0) << '\n';
  }

  return 0;
}
