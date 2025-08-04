#include <bits/stdc++.h>
using namespace std;

const int N = 300005;
int n, k, a[N];
string s;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;
  while (t--) {
    cin >> n >> k >> s;
    for (int i = 1; i <= n; i++)
      cin >> a[i];
    s = " " + s; // para indexar desde 1

    int left = 0, right = 1e9;
    while (left < right) {
      int mid = (left + right) / 2;

      int countB = 0;
      char current = 0;
      for (int i = 1; i <= n; i++) {
        if (a[i] > mid) {
          if (current != s[i]) {
            current = s[i];
            if (s[i] == 'B')
              countB++;
          }
        }
      }

      if (countB <= k)
        right = mid;
      else
        left = mid + 1;
    }

    cout << right << "\n";
  }

  return 0;
}