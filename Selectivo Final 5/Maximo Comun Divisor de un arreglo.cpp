#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int N = 200001;
const int MOD = 1e9 + 7;

int smallestPrime[N];

vector<map<int, int>> factors;
map<int, multiset<int>> minPowers;
ll currentGcd = 1;

void sieve() {
  iota(smallestPrime, smallestPrime + N, 0);

  for (int i = 2; i * i < N; i++) {
    if (smallestPrime[i] == i) {
      for (int j = i * i; j < N; j += i) {
        if (smallestPrime[j] == j)
          smallestPrime[j] = i;
      }
    }
  }
}

// n = p1^k1, p2^k2, ... pi^ki
map<int, int> getFactors(int n) {
  map<int, int> factors;
  while (n != 1) {
    factors[smallestPrime[n]]++;
    n /= smallestPrime[n];
  }
  return factors;
}

ll power(ll base, ll exp) {
  ll res = 1;
  base %= MOD;
  while (exp > 0) {
    if (exp % 2 == 1)
      res = (res * base) % MOD;
    base = (base * base) % MOD;
    exp /= 2;
  }
  return res;
}

void updateGcd(int prime, int newMinPower) {
  currentGcd = (currentGcd * power(prime, newMinPower)) % MOD;
}

int main() {
  cin.tie(0)->sync_with_stdio();
  cout.tie(0);

  sieve();

  int n, q;
  cin >> n >> q;

  factors.resize(n);
  for (int i = 0; i < n; i++) {
    int a;
    cin >> a;
    factors[i] = getFactors(a);
    for (auto& [prime, power] : factors[i]) {
      minPowers[prime].insert(power);
    }
  }

  for (auto [prime, powers] : minPowers) {
    if (powers.size() == n) {
      updateGcd(prime, *powers.begin());
    }
  }

  while (q--) {
    int i, x;
    cin >> i >> x;
    i--;

    map<int, int> factorsX = getFactors(x);
    for (auto [prime, powerX] : factorsX) {
      int prevMinPower = 0;
      if (minPowers[prime].size() == n)
        prevMinPower = *minPowers[prime].begin();

      if (factors[i].count(prime)) {
        auto it = minPowers[prime].find(factors[i][prime]);
        minPowers[prime].erase(it);
      }

      factors[i][prime] += powerX;
      minPowers[prime].insert(factors[i][prime]);

      int newMinPower = 0;
      if (minPowers[prime].size() == n)
        newMinPower = *minPowers[prime].begin();

      if (newMinPower > prevMinPower)
        updateGcd(prime, newMinPower - prevMinPower);
    }
    cout << currentGcd << '\n';
  }

  return 0;
}
