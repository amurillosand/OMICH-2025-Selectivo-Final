#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m, tc = 1;

  while (cin >> n >> m) {
    set<int> digits;
    for (int d = 0; d <= 9; d++) {
      digits.insert(d);
    }

    for (int i = 0; i < m; i++) {
      int d;
      cin >> d;
      digits.erase(d);
    }

    vector<bool> vis(n, false);
    vector<int> parentRem(n, -1);
    vector<char> parentDig(n, 0);

    queue<int> bfs;
    for (int d : digits) {
      if (d == 0)
        continue;
      int r = d % n;
      if (!vis[r]) {
        vis[r] = true;
        parentRem[r] = -1;
        parentDig[r] = char('0' + d);
        bfs.push(r);
      }
    }

    string ans = "-1";
    while (!bfs.empty() && !vis[0]) {
      int cur = bfs.front();
      bfs.pop();
      for (int d : digits) {
        int nxt = (cur * 10 + d) % n;
        if (!vis[nxt]) {
          vis[nxt] = true;
          parentRem[nxt] = cur;
          parentDig[nxt] = char('0' + d);
          bfs.push(nxt);
          if (nxt == 0)
            break;
        }
      }
    }

    if (vis[0]) {
      string s;
      for (int cur = 0; cur != -1; cur = parentRem[cur]) {
        s.push_back(parentDig[cur]);
      }
      reverse(s.begin(), s.end());
      ans = s;
    }

    cout << "Case " << tc++ << ": " << ans << "\n";
  }

  return 0;
}
