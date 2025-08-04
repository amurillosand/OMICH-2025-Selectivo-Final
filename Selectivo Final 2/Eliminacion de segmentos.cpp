#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

#define l first
#define r second

int a[N];
int nxt[N], prev[N];

using ii = pair<int, int>;

struct Dsu {
  vector<int> par, total;
  vector<ii> range;
  set<ii> groups; // order by size, then by smallest index

  Dsu(int n) : par(n), total(n, 1), range(n) {
    iota(par.begin(), par.end(), 0);
    for (int i = 1; i < n; ++i) {
      range[i] = {i, i};
      groups.insert({-total[i], i});
    }
  }

  int find(int x) {
    return par[x] == x ? x : par[x] = find(par[x]);
  }

  ii rangeOf(int i) {
    return range[find(i)];
  }

  bool unite(int l, int r) {
    l = find(l), r = find(r);
    if (l != r) {
      if (l > r) {
        swap(l, r);
      }

      groups.erase({-total[l], l});
      groups.erase({-total[r], r});

      total[l] += total[r];
      groups.insert({-total[l], l});

      range[l].l = min(range[l].l, range[r].l);
      range[l].r = max(range[l].r, range[r].r);

      par[r] = l;

      return true;
    }
    return false;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  while (cin >> n) {

    Dsu dsu(n + 2);
    a[0] = -1;
    a[n + 1] = -2;
    for (int i = 1; i <= n; ++i) {
      cin >> a[i];

      ::prev[i] = i - 1;
      ::nxt[i] = i + 1;

      if (a[i] == a[i - 1]) {
        dsu.unite(i - 1, i);
      }
    }

    int total = 0;
    while (dsu.groups.size() > 1) {
      int id = dsu.groups.begin()->second;

      dsu.groups.erase(dsu.groups.begin());

      int l = dsu.rangeOf(id).l;
      int r = dsu.rangeOf(id).r;

      // "clear" the gap in between l and r
      ::nxt[::prev[l]] = ::nxt[r];
      ::prev[::nxt[r]] = ::prev[l];

      // connect left and right if they have the same value
      if (a[::nxt[r]] == a[::prev[l]]) {
        dsu.unite(::nxt[r], ::prev[l]);
      }

      total++;
    }

    cout << total << '\n';
  }

  return 0;
}