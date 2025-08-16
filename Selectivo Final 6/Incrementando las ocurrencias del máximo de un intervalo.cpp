#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
  #include "debug.h"
#else
  #define debug(...)
#endif

using lli = long long;

const lli INF = 1e18;
const int N = 1e6 + 1;

lli a[N];
int n;

struct LazySegmentTree {
  int l, r;
  LazySegmentTree *left, *right;
  lli mx = 0, lazy = 0;

  LazySegmentTree(int l, int r) : l(l), r(r), left(0), right(0) {
    if (l == r) {
      mx = a[l];
      return;
    }
    int m = (l + r) >> 1;
    left = new LazySegmentTree(l, m);
    right = new LazySegmentTree(m + 1, r);
    pull();
  }

  int value() {
    // the actual value of the node, remember, we're updating lazily
    return mx + lazy;
  }

  void push() {
    if (!lazy)
      return;

    if (l != r) {
      // propagate update only if their values are equal to mx
      if (left->value() == mx)
        left->lazy += lazy;
      if (right->value() == mx)
        right->lazy += lazy;
    }

    // update the current node
    mx += lazy;
    lazy = 0;
  }

  void pull() {
    mx = max(left->mx, right->mx);
  }

  void update(int ll, int rr, lli v) {
    push();
    // out of range or node doesn't have the same value as v
    if (rr < l || r < ll || mx < v)
      return;
    if (ll <= l && r <= rr) {
      lazy++;
      push();
      return;
    }
    left->update(ll, rr, v);
    right->update(ll, rr, v);
    pull();
  }

  lli query(int ll, int rr) {
    push();
    if (rr < l || r < ll)
      return 0;
    if (ll <= l && r <= rr)
      return mx;
    return max(left->query(ll, rr), right->query(ll, rr));
  }

  lli at(int i) {
    return query(i, i);
  }
};

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n;
  cin >> n;
  for (int i = 0; i < n; i++)
    cin >> a[i];

  LazySegmentTree tree(0, n - 1);

  int q;
  cin >> q;
  while (q--) {
    int l, r;
    cin >> l >> r;
    r--;

    lli mx = tree.query(l, r);
    debug(l, r, mx);

    tree.update(l, r, mx);
  }

  for (int i = 0; i < n; i++)
    cout << tree.at(i) << ' ';

  return 0;
}
