#include <bits/stdc++.h>
using namespace std;

using lli = long long;
using ii = pair<int, int>;

const int N = 1e6 + 5;
const int SQRT = 500;
lli a[N];
int n;

struct Block {
  map<lli, unordered_set<int>> where;
  lli mx;

  void updateSingleElement(int pos, lli lazy) {
    where[a[pos]].erase(pos);
    if (where[a[pos]].empty()) {
      where.erase(a[pos]);
    }

    a[pos] += lazy;
    where[a[pos]].insert(pos);

    mx = max(mx, a[pos]);
  }

  void updateAllElementsWithValue(lli val, lli lazy) {
    auto it = where.find(val);
    lli nval = val + lazy;

    if (it != where.end()) {
      where[nval] = std::move(it->second);
      where.erase(val);

      for (int pos : where[nval])
        a[pos] = nval;

      mx = max(mx, nval);
    }
  }

  Block() {}

  Block(int l, int r) {
    mx = -1;
    for (int i = l; i <= r; ++i) {
      where[a[i]].insert(i);
      mx = max(mx, a[i]);
    }
  }
};

Block block[N / SQRT + 5];
bool startOfBlock[N];
int id[N];
int sqn;

lli query(int l, int r) {
  lli mx = -1;
  while (l <= r) {
    if (l + sqn - 1 <= r && startOfBlock[l]) {
      mx = max(mx, block[id[l]].mx);
      l += sqn;
    } else {
      mx = max(mx, a[l]);
      l++;
    }
  }
  return mx;
}

void update(int l, int r, lli mx, lli add) {
  while (l <= r) {
    if (l + sqn - 1 <= r && startOfBlock[l]) {
      if (block[id[l]].mx == mx) {
        block[id[l]].updateAllElementsWithValue(mx, add);
      }
      l += sqn;
    } else {
      if (a[l] == mx) {
        block[id[l]].updateSingleElement(l, add);
      }
      l++;
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  cin >> n;
  sqn = sqrt(n);

  for (int i = 0; i < n; ++i) {
    cin >> a[i];
    id[i] = i / sqn;
  }

  for (int l = 0; l < n; l += sqn) {
    startOfBlock[l] = true;
    int r = min(n - 1, l + sqn - 1);
    block[id[l]] = Block(l, r);
  }

  int q;
  cin >> q;

  int lastL = -1, lastR = -1;
  lli add = 1;

  while (q--) {
    int l, r;
    cin >> l >> r;
    r--;

    if (l == lastL && r == lastR) {
      add++;
      lastL = l, lastR = r;
    } else {
      lli mx = query(l, r);
      update(l, r, mx, add);
      add = 1;
      lastL = -1, lastR = -1;
    }
  }

  if (lastL != -1) {
    update(lastL, lastR, query(lastL, lastR), add);
  }

  for (int i = 0; i < n; ++i) {
    cout << a[i] << ' ';
  }
  cout << '\n';

  return 0;
}
