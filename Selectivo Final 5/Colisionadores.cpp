#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
int smallestPrime[N];

void sieve() {
  for (int i = 2; i <= N; i++)
    smallestPrime[i] = i;

  for (int i = 2; i * i <= N; i++) {
    if (smallestPrime[i] == i) {
      for (int j = i * i; j <= N; j += i) {
        if (smallestPrime[j] == j)
          smallestPrime[j] = i;
      }
    }
  }
}

vector<int> getFactors(int x) {
  vector<int> factors;
  while (x > 1) {
    int p = smallestPrime[x];
    factors.push_back(p);
    while (x % p == 0)
      x /= p;
  }
  return factors;
}

int main() {
  cin.tie(0)->sync_with_stdio();
  cout.tie(0);

  sieve();

  int n, m;
  cin >> n >> m;

  vector<bool> isActive(n + 1, false);
  unordered_map<int, int> factorOccupied;

  while (m--) {
    char op;
    int i;
    cin >> op >> i;

    if (op == '+') {
      if (isActive[i]) {
        cout << "Already on\n";
        continue;
      }

      vector<int> factors = getFactors(i);
      int conflict = -1;
      for (int f : factors) {
        if (factorOccupied.count(f)) {
          conflict = factorOccupied[f];
          break;
        }
      }

      if (conflict != -1) {
        cout << "Conflict with " << conflict << '\n';
      } else {
        isActive[i] = true;
        for (int f : factors)
          factorOccupied[f] = i;
        cout << "Success\n";
      }
    } else {
      if (!isActive[i]) {
        cout << "Already off\n";
        continue;
      }

      vector<int> factors = getFactors(i);
      isActive[i] = false;
      for (int f : factors) {
        if (factorOccupied[f] == i)
          factorOccupied.erase(f);
      }
      cout << "Success\n";
    }
  }

  return 0;
}
