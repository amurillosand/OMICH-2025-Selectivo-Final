#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5, SQ = 316;

int block[N], nxt[N], lastPos[N], cnt[N], a[N];
int n, m;

void update(int i) {
  int j = i + a[i];
  if (j > n) {
    nxt[i] = N;
    lastPos[i] = i;
    cnt[i] = 1;
  } else if (block[i] != block[j]) {
    nxt[i] = j;
    lastPos[i] = j;
    cnt[i] = 1;
  } else {
    nxt[i] = nxt[j];
    lastPos[i] = lastPos[j];
    cnt[i] = cnt[j] + 1;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    block[i] = i / SQ;
  }
  for (int i = n; i >= 1; i--)
    update(i);

  while (m--) {
    int op, p;
    cin >> op >> p;
    if (op == 0) {
      cin >> a[p];
      for (int i = p; i >= 1 && block[i] == block[p]; i--)
        update(i);
    } else {
      int total = 0, last = p;
      while (p <= n) {
        total += cnt[p];
        last = lastPos[p];
        p = nxt[p];
      }
      cout << last << " " << total << "\n";
    }
  }

  return 0;
}
