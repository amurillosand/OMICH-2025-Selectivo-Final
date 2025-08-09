#include <bits/stdc++.h>
#ifdef LOCAL
  #include "debug.h"
#else
  #define debug(...) 42
#endif

using namespace std;

const int N = 100005;
const long long INF = 1e18;
const int MOD1 = 1000000007;
const int MOD2 = 1000000021;

int n, m, s, t;
int u[N], v[N];
long long w[N];
long long dist[2][N]; // dist[0] for s→t, dist[1] for t→s
long long countPaths1[2][N]; // for modulo MOD1
long long countPaths2[2][N]; // for modulo MOD2
vector<pair<int, int>> adj[2][N]; // adj[0] normal, adj[1] reversed

void dijkstra(int start,
              vector<pair<int, int>> graph[],
              long long dist[],
              long long count1[],
              long long count2[]) {
  fill(dist, dist + n + 1, INF);
  fill(count1, count1 + n + 1, 0);
  fill(count2, count2 + n + 1, 0);

  priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;

  dist[start] = 0;
  count1[start] = 1;
  count2[start] = 1;
  pq.emplace(0, start);

  while (!pq.empty()) {
    auto [d, node] = pq.top();
    pq.pop();

    if (d > dist[node])
      continue;

    for (const auto& [neighbor, weight] : graph[node]) {
      long long newDist = dist[node] + weight;
      if (newDist < dist[neighbor]) {
        dist[neighbor] = newDist;
        count1[neighbor] = count1[node];
        count2[neighbor] = count2[node];
        pq.emplace(newDist, neighbor);
      } else if (newDist == dist[neighbor]) {
        count1[neighbor] = (count1[neighbor] + count1[node]) % MOD1;
        count2[neighbor] = (count2[neighbor] + count2[node]) % MOD2;
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m >> s >> t;

  for (int i = 0; i < m; ++i) {
    cin >> u[i] >> v[i] >> w[i];
    adj[0][u[i]].emplace_back(v[i], w[i]); // original graph
    adj[1][v[i]].emplace_back(u[i], w[i]); // reversed graph
  }

  dijkstra(s, adj[0], dist[0], countPaths1[0], countPaths2[0]);
  dijkstra(t, adj[1], dist[1], countPaths1[1], countPaths2[1]);

  long long totalPaths1 = countPaths1[0][t];
  long long totalPaths2 = countPaths2[0][t];
  long long shortestPathLength = dist[0][t];

  int yes = 0, no = 0, repair = 0;
  for (int i = 0; i < m; ++i) {
    // la arista es u->v
    long long forward = dist[0][u[i]]; // s->t, s->u
    long long backward = dist[1][v[i]]; // t->s, t->v
    long long total = forward + w[i] + backward;

    bool isUnique = (total == shortestPathLength &&
                     (countPaths1[0][u[i]] * countPaths1[1][v[i]] % MOD1 == totalPaths1) &&
                     (countPaths2[0][u[i]] * countPaths2[1][v[i]] % MOD2 == totalPaths2));

    if (isUnique) {
      cout << "Si\n";
      yes++;
    } else {
      long long repairCost = total - shortestPathLength + 1;
      if (repairCost < w[i]) {
        cout << "Reparar " << repairCost << '\n';
        repair++;
      } else {
        cout << "No\n";
        no++;
      }
    }
  }

  debug(yes, no, repair);

  return 0;
}
