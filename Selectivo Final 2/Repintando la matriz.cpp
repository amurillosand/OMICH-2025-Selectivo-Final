#include <bits/stdc++.h>
using namespace std;

const int N = 55;
int n, m, dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};
char ar[N][N];

bool is_val(int i, int j) {
  return i >= 0 && i < n && j >= 0 && j < m;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin >> n >> m;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      cin >> ar[i][j];

  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      if (ar[i][j] == '#') {
        int cnt = 0;
        for (int k = 0; k < 4; k++) {
          int x = i + dx[k], y = j + dy[k];
          if (is_val(x, y) && ar[x][y] == '#')
            cnt++;
        }
        if (!cnt)
          return cout << "No\n", 0;
      }

  cout << "Si\n";

  return 0;
}