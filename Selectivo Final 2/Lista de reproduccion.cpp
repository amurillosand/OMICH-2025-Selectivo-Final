#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0), cout.tie(0);

  int n;
  cin >> n;

  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }

  int ans = 0;
  set<int> st;
  int l = 0, r = 0;
  while (l < n) {
    while (r < n && !st.count(a[r])) {
      st.insert(a[r]);
      ans = max(ans, r - l + 1);
      r++;
    }

    st.erase(a[l]);
    l++;
  }

  cout << ans << '\n';

  return 0;
}