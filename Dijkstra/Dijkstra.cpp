#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"

#include <bits/stdc++.h>

using namespace std;

const int maxn = 100;
int adjMat[maxn][maxn];
bool visited[maxn];
float dist[maxn];
int parent[maxn];

void addEdge(int from, int to, int weight);
void dijkstra(int V);
void readWeightedGraph();
void printAllShortestPaths(int);

int main() {
  const auto start = chrono::high_resolution_clock::now();
  fstream in("test.txt");
  cin.rdbuf(in.rdbuf());
  int t;
  cin >> t;
  while (t--) {
    readWeightedGraph();
    memset(adjMat, 0, sizeof adjMat);
  }
  const auto end = chrono::high_resolution_clock::now();
  cout << "Time elapsed: "
       << chrono::duration_cast<chrono::microseconds>(end - start).count()
       << "us";
  return 0;
}

void addEdge(int from, int to, int weight) {
  adjMat[from][to] = adjMat[to][from] = weight;
}

int minDistance(int V) {
  float min = INFINITY;
  int minIndex;
  for (int v = 0; v < V; v++)
    if (!visited[v] && dist[v] <= min) min = dist[v], minIndex = v;
  return minIndex;
}

void dijkstra(int V) {
  for (int i = 0; i < V; i++) {
    dist[i] = INFINITY;
    parent[i] = -1;
    visited[i] = false;
  }
  dist[0] = 0;
  for (int count = 0; count + 1 < V; count++) {
    int minDist = minDistance(V);
    visited[minDist] = true;
    for (int v = 0; v < V; v++)
      if (!visited[v] && adjMat[minDist][v] &&
          dist[minDist] + (float)adjMat[minDist][v] < dist[v]) {
        dist[v] = dist[minDist] + (float)adjMat[minDist][v];
        parent[v] = minDist;
      }
  }
}

void readWeightedGraph() {
  int V, E;
  cin >> V >> E;
  for (int i = 0; i < E; ++i) {
    int from, to, weight;
    cin >> from >> to >> weight;
    addEdge(from - 1, to - 1, weight);
  }
  dijkstra(V);
  cout << "\nAll paths: \n";
  printAllShortestPaths(V);
}

void printAllShortestPaths(int V) {
  stack<int> path;
  for (int i = 1; i < V; i++) {
    path.push(i);
    for (int iter = parent[i]; iter != -1; iter = parent[iter]) path.push(iter);
    while (!path.empty()) {
      cout << fixed << setprecision(0) << path.top() + 1 << ' ';
      path.pop();
    }
    cout << " -> " << dist[i] << endl;
  }
}

#pragma clang diagnostic pop