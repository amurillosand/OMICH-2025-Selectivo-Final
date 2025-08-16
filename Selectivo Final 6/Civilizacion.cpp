#include <bits/stdc++.h>
using namespace std;

typedef long long Lli;

const int N = 3e5 + 5;

struct Dsu {
  vector<int> parent, rank, maxPath;

  Dsu(int nn = 0) {
    parent.resize(nn + 5);
    iota(parent.begin(), parent.end(), 0);
    rank.resize(nn + 5, 0);
    maxPath.resize(nn + 5, 0);
  }

  int find(int u) {
    return parent[u] == u ? u : parent[u] = find(parent[u]);
  }

  void unite(int u, int v) {
    u = find(u), v = find(v);
    if (u != v) {
      if (rank[u] > rank[v])
        swap(u, v);
      parent[u] = v;

      maxPath[v] = max({
        maxPath[u], 
        maxPath[v], 
        (maxPath[u] + 1) / 2 + (maxPath[v] + 1) / 2 + 1 // take 2 "radio" sum down
      });
      
      if (rank[u] == rank[v])
        rank[v]++;
    }
  }

  int longestPath(int u) {
    return maxPath[find(u)];
  }
};

vector<int> graph[N];
bool visited[N];
Dsu dsuGraph;
int nodeCount, edgeCount, queryCount;

// Returns (distance, node) of farthest node from u
pair<int, int> dfs(int u, int parent = 0) {
  visited[u] = true;
  pair<int, int> farthest = {-1, u};
  for (int v : graph[u]) {
    if (v != parent) {
      farthest = max(farthest, dfs(v, u));
    }
  }
  farthest.first++;
  return farthest;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> nodeCount >> edgeCount >> queryCount;
  dsuGraph = Dsu(nodeCount);

  for (int i = 0; i < edgeCount; ++i) {
    int u, v;
    cin >> u >> v;
    graph[u].push_back(v);
    graph[v].push_back(u);
    dsuGraph.unite(u, v);
  }

  for (int u = 1; u <= nodeCount; ++u) {
    dsuGraph.maxPath[u] = 0;
  }

  for (int u = 1; u <= nodeCount; ++u) {
    if (!visited[u]) {
      dsuGraph.maxPath[dsuGraph.find(u)] = dfs(dfs(u).second).first;
    }
  }

  while (queryCount--) {
    int type, u, v;
    cin >> type >> u;
    if (type == 1) {
      cout << dsuGraph.longestPath(u) << '\n';
    } else {
      cin >> v;
      dsuGraph.unite(u, v);
    }
  }

  return 0;
}
