#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"

#include <bits/stdc++.h>

using namespace std;

const int maxn = 100;
vector<int> adj[maxn];
bool visited[maxn];

bool isCyclicUtil(int v, int parent);
bool isCyclic(int V);
void addEdge(int u, int v);

int main() {
  fstream in("test.txt");
  cin.rdbuf(in.rdbuf());
  int V, E;
  cin >> V >> E;
  for (int i = 0; i < E; ++i) {
    int u, v;
    cin >> u >> v;
    addEdge(u-1,v-1);
  }
  cout << "The tree cyclization is: " << (isCyclic(V) ? "Yes" : "No");
  return 0;
}

bool isCyclicUtil(int v, int parent) {
  visited[v] = true;
  for (int i: adj[v])
    if (!visited[i]) {
      if (isCyclicUtil(i, v))
        return true;
    } else if (i != parent)
      return true;
  return false;
}

bool isCyclic(int V) {
  memset(visited, 0, sizeof visited);
  for (int i = 0; i < V; ++i)
    if (!visited[i])
      if (isCyclicUtil(i, -1))
        return true;
  return false;
}

void addEdge(int u, int v) {
  adj[u].push_back(v);
  adj[v].push_back(u);
}

#pragma clang diagnostic pop