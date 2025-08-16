#include <bits/stdc++.h>
using namespace std;

int lis(const vector<int>& a) {
  vector<int> dp;
  for (int x : a) {
    // quiero abrir un lis con x al final, se puede?
    auto it = lower_bound(dp.begin(), dp.end(), x);
    if (it == dp.end())
      dp.push_back(x);
    else
      *it = x;
  }
  return dp.size();
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int n;
  cin >> n;

  vector<pair<int, int>> ab(n);
  for (int i = 0; i < n; ++i)
    cin >> ab[i].first;
  for (int i = 0; i < n; ++i)
    cin >> ab[i].second;

  sort(ab.begin(), ab.end());

  vector<int> b(n);
  for (int i = 0; i < n; ++i)
    b[i] = ab[i].second;

  cout << n + lis(b) << '\n';

  return 0;
}
