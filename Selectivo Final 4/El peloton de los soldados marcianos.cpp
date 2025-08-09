#include <bits/stdc++.h>
using namespace std;

int n, sectionSize;
string s;
vector<int> prefix[3];

inline int charIndex(char c) {
  return c - 'A';
}

int getCount(int l, int r, int c) {
  return prefix[c][r] - prefix[c][l];
}

int calculateSwaps(const array<int, 3>& target) {
  int counts[3][3];
  for (int i = 0; i < 3; i++) {
    int l = i * sectionSize, r = l + sectionSize;
    for (int j = 0; j < 3; j++) {
      counts[i][j] = getCount(l, r, j);
    }
  }
  int s01 = min(counts[0][target[1]], counts[1][target[0]]);
  int s02 = min(counts[0][target[2]], counts[2][target[0]]);
  int s12 = min(counts[1][target[2]], counts[2][target[1]]);
  int direct = s01 + s02 + s12;
  int misplaced1 = sectionSize - counts[0][target[0]];
  int misplaced2 = sectionSize - counts[1][target[1]];
  int misplaced3 = sectionSize - counts[2][target[2]];
  int totalMisplaced = misplaced1 + misplaced2 + misplaced3;
  int remaining = totalMisplaced - 2 * direct;
  return direct + 2 * remaining / 3;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> s;
  n = s.size();
  sectionSize = n / 3;

  for (int c = 0; c < 3; c++)
    prefix[c].assign(n + 1, 0);
  for (int i = 0; i < n; i++) {
    for (int c = 0; c < 3; c++)
      prefix[c][i + 1] = prefix[c][i];
    prefix[charIndex(s[i])][i + 1]++;
  }

  string letters = "ABC";
  array<int, 3> perm;
  int ans = 1e9;
  sort(letters.begin(), letters.end());
  do {
    for (int i = 0; i < 3; i++)
      perm[i] = charIndex(letters[i]);
    ans = min(ans, calculateSwaps(perm));
  } while (next_permutation(letters.begin(), letters.end()));

  cout << ans << "\n";

  return 0;
}
