#include <bits/stdc++.h>
using namespace std;

#define all(a) (a).begin(), (a).end()

const int N = 1005;
int n, m;

bool valid(int r, int c) {
  return 0 <= r && r < n && 0 <= c && c < m;
}

const int dr[4] = {1, 0, -1, 0};
const int dc[4] = {0, 1, 0, -1};

struct Cell {
  int r, c;
  int height;
  int ans = 0;

  int index() const {
    return r * m + c;
  }

  static pair<int, int> reverseIndex(int index) {
    return {index / m, index % m};
  }
} grid[N][N];

struct Dsu {
  vector<int> parent;
  vector<vector<int>> path;

  Dsu(int n) : parent(n), path(n) {
    iota(parent.begin(), parent.end(), 0);
    for (int i = 0; i < n; ++i) {
      path[i].emplace_back(i);
    }
  }

  int find(int i) {
    if (parent[i] != i)
      parent[i] = find(parent[i]);
    return parent[i];
  }

  int height(int i) {
    auto [r, c] = Cell::reverseIndex(i);
    return grid[r][c].height;
  }

  void unite(int u, int v) {
    int currentHeight = height(u);

    u = find(u);
    v = find(v);

    if (u == v)
      return;

    if (height(u) > height(v)) {
      swap(u, v); // Ensure: height(u) <= height(v)
    }

    // The topographic prominence of a cell is:
    // • the cell’s elevation, if there is no other strictly higher cell
    // • cell height minus the highest elevation of the lowest cell on a path going to a strictly
    // higher cell.

    // Now height(v) >= height(u)

    if (height(v) > height(u)) {
      // This means we are merging a **lower component** (u) into a strictly **higher** one (v)

      // So all the points in component u have now "found" a path to a strictly higher point  -> we
      // update their prominence
      for (int i : path[u]) {
        auto [r, c] = Cell::reverseIndex(i);
        grid[r][c].ans = height(i) - currentHeight;
      }
      path[u].clear();
    }

    // Merge the paths of u and v, ensuring the smaller path is added to the larger one
    if (path[u].size() > path[v].size())
      swap(u, v);
    for (int i : path[u]) {
      path[v].emplace_back(i);
    }

    parent[u] = v;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> n >> m;

  int k = n * m;
  Dsu dsu(k);
  vector<pair<int, int>> order;
  order.reserve(k);

  for (int r = 0; r < n; ++r) {
    for (int c = 0; c < m; ++c) {
      Cell& cell = grid[r][c];
      cin >> cell.height;
      cell.r = r;
      cell.c = c;
      cell.ans = cell.height; // Initialize prominence to height

      order.emplace_back(cell.height, cell.index());
    }
  }

  sort(order.rbegin(), order.rend());

  for (auto [height, i] : order) {
    auto [r, c] = Cell::reverseIndex(i);

    for (int dir = 0; dir < 4; ++dir) {
      int nr = r + dr[dir];
      int nc = c + dc[dir];

      // Check if the neighboring cell is valid and has a height greater than or equal to the
      // current cell's height, if so unite them and calculate prominence
      if (valid(nr, nc) && grid[nr][nc].height >= height) {
        dsu.unite(grid[r][c].index(), grid[nr][nc].index());
      }
    }
  }

  for (int r = 0; r < n; ++r) {
    for (int c = 0; c < m; ++c) {
      cout << grid[r][c].ans << " ";
    }
    cout << "\n";
  }

  return 0;
}
