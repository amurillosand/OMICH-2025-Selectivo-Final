#include <bits/stdc++.h>
using namespace std;

using lli = long long;

struct RollingHash {
  static const lli MOD = 1000000007;
  static const lli BASE = 131;
  vector<lli> power, hashFwd, hashBwd;
  int n;

  RollingHash(const string& s) {
    n = (int)s.size();
    power.assign(n + 1, 1);
    for (int i = 1; i <= n; i++) {
      power[i] = (power[i - 1] * BASE) % MOD;
    }

    hashFwd.assign(n + 1, 0);
    for (int i = 0; i < n; i++) {
      hashFwd[i + 1] = (hashFwd[i] * BASE + s[i]) % MOD;
    }

    hashBwd.assign(n + 1, 0);
    for (int i = 0; i < n; i++) {
      hashBwd[i + 1] = (hashBwd[i] * BASE + s[n - 1 - i]) % MOD;
    }
  }

  // get forward hash of s[l..r-1]
  lli getFHash(int l, int r) {
    int length = r - l;
    lli val = hashFwd[r] - (hashFwd[l] * power[length]) % MOD;
    if (val < 0)
      val += MOD;
    return val;
  }

  // get backward hash of s[l..r-1] reversed substring
  lli getBHash(int l, int r) {
    int length = r - l;
    lli val = hashBwd[r] - (hashBwd[l] * power[length]) % MOD;
    if (val < 0)
      val += MOD;
    return val;
  }
};

string makePalindrome(const string& s) {
  int n = (int)s.size();
  RollingHash rh(s);

  for (int i = 0; i < n; i++) {
    int length = n - i;
    if (rh.getFHash(i, n) == rh.getBHash(0, length)) {
      // s[i..n-1] is palindrome
      string toAdd = s.substr(0, i);
      reverse(toAdd.begin(), toAdd.end());
      return s + toAdd;
    }
  }

  return s;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string s;

  while (cin >> s) {
    cout << makePalindrome(s) << "\n";
  }

  return 0;
}
