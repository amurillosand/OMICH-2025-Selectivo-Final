#include <bits/stdc++.h>
using namespace std;

using lli = long long;

const int N = 105;
const int T = 505;
const lli INF = 1e18;

const int dx[] = {1, 1, 1, 0, 0, 0, -1, -1, -1};
const int dy[] = {1, 0, -1, 1, 0, -1, 1, 0, -1};

lli mem[N][N][T];
bitset<T> done[N][N];
lli start[N][N];
lli again[N][N];
lli points[N][N];
int n, m, t;

bool valid(lli x, lli y) {
  return (0 <= x && x < n && 0 <= y && y < m);
}

lli dp(lli x, lli y, lli cur) {
  if (!valid(x, y))
    return -INF;

  if (cur > t)
    return 0;

  lli& ans = mem[x][y][cur];
  if (!done[x][y][cur]) {
    done[x][y][cur] = 1;
    ans = 0;

    lli gain = 0;
    if (cur >= start[x][y] && (cur - start[x][y]) % again[x][y] == 0)
      gain = points[x][y];

    for (int dir = 0; dir < 9; dir++) {
      int nx = x + dx[dir];
      int ny = y + dy[dir];

      lli tmp = dp(nx, ny, cur + 1);

      ans = max(ans, tmp);
    }

    ans += gain;
  }

  return ans;
}

int main() {
  cin.tie(0)->sync_with_stdio(false);
  cout.tie(0);

  cin >> n >> m >> t;

  for (int x = 0; x < n; x++) {
    for (int y = 0; y < m; y++) {
      cin >> start[x][y];
    }
  }

  for (int x = 0; x < n; x++) {
    for (int y = 0; y < m; y++) {
      cin >> again[x][y];
    }
  }

  for (int x = 0; x < n; x++) {
    for (int y = 0; y < m; y++) {
      cin >> points[x][y];
    }
  }

  lli ans = 0;
  for (int x = 0; x < n; x++) {
    for (int y = 0; y < m; y++) {
      ans = max(ans, dp(x, y, 1));
    }
  }

  cout << ans << '\n';

  return 0;
}