#include <bits/stdc++.h>
using namespace std;

vector<int> fib;
int n;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  fib.push_back(1);
  fib.push_back(2);

  while (cin >> n) {
    while (fib.back() <= n) {
      int next = fib[fib.size() - 1] + fib[fib.size() - 2];
      if (next > n)
        break;
      fib.push_back(next);
    }

    vector<int> ans;
    while (n > 0) {
      auto it = upper_bound(fib.begin(), fib.end(), n);
      if (it == fib.begin()) {
        break; // No valid Fibonacci number found
      }
      --it; // Get the largest Fibonacci number less than or equal to n
      ans.push_back(it - fib.begin() + 1);
      n -= *it;
    }

    cout << ans.size() << "\n";
    for (auto x : ans) {
      cout << x << " ";
    }
    cout << "\n";
  }

  return 0;
}