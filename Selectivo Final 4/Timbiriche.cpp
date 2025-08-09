#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> Edge;

Edge makeEdge(int a, int b) {
  if (a > b)
    swap(a, b);
  return {a, b};
}

int main() {
  int n, m;
  cin >> n >> m;

  vector<Edge> moves(m);
  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    moves[i] = makeEdge(a, b);
  }

  vector<set<Edge>> squares;
  for (int row = 0; row < n - 1; ++row) {
    for (int col = 0; col < n - 1; ++col) {
      int topLeft = row * n + col + 1;
      int topRight = topLeft + 1;
      int bottomLeft = topLeft + n;
      int bottomRight = bottomLeft + 1;

      set<Edge> square = {makeEdge(topLeft, topRight),
                          makeEdge(topLeft, bottomLeft),
                          makeEdge(topRight, bottomRight),
                          makeEdge(bottomLeft, bottomRight)};
      squares.push_back(square);
    }
  }

  set<Edge> drawnLines;
  int score[2] = {0, 0};
  int player = 0;

  for (auto [a, b] : moves) {
    Edge e = makeEdge(a, b);
    drawnLines.insert(e);

    int completed = 0;
    for (auto& square : squares) {
      if (square.count(e) &&
          includes(drawnLines.begin(), drawnLines.end(), square.begin(), square.end())) {
        completed++;
      }
    }

    if (completed > 0) {
      score[player] += completed;
    } else {
      player ^= 1;
    }
  }

  cout << score[0] << " " << score[1] << endl;
  return 0;
}