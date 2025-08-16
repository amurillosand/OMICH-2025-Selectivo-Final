#include <bits/stdc++.h>
using namespace std;

int main() {
  int M;
  cin >> M;
  if (M <= 4) {
    cout << 0 << endl;
    return 0;
  }

  vector<bool> isPrime(M, true);
  isPrime[0] = isPrime[1] = false;
  for (int i = 2; i * i < M; i++) {
    if (isPrime[i]) {
      for (int j = i * i; j < M; j += i)
        isPrime[j] = false;
    }
  }

  vector<int> primes;
  for (int i = 2; i < M; i++) {
    if (isPrime[i])
      primes.push_back(i);
  }

  vector<bool> isSemiprime(M, false);
  for (int i = 0; i < primes.size(); i++) {
    for (int j = i; j < primes.size(); j++) {
      long long product = (long long)primes[i] * primes[j];
      if (product >= M)
        break;
      isSemiprime[product] = true;
    }
  }

  int count = 0;
  for (int i = 4; i < M; i++) {
    if (isSemiprime[i])
      count++;
  }
  cout << count << '\n';

  return 0;
}