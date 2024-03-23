#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"

#include <bits/stdc++.h>

using namespace std;

const int maxn = 100;
vector<int> adj[maxn];
bool visited[maxn];
stack<int> result;

void topologicalSort(int V);
void topologicalSortUtil(int s, int V);
void addEdge(int from, int to);
void readAndProcess();

int main() {
  fstream in("test.txt");
  cin.rdbuf(in.rdbuf());
  int t;
  cin >> t;
  while (t--) {
    readAndProcess();
    memset(visited, 0, sizeof visited);
    for (auto &i: adj)
      i.clear();
    cout << endl;
  }
  return 0;
}

void readAndProcess() {
  int V, E, u, v;
  cin >> V >> E;
  for (int i = 0; i < E; ++i) {
    cin >> u >> v;
    addEdge(u - 1, v - 1);
  }
  topologicalSort(V);
}

void topologicalSort(int V) {
  memset(visited, 0, V);
  for (int i = 0; i < V; i++)
    if (!visited[i])
      topologicalSortUtil(i, V);
  while (!result.empty()) {
    cout << result.top() + 1 << ' ';
    result.pop();
  }
}

void topologicalSortUtil(int s, int V) {
  visited[s] = true;
  for (int i: adj[s])
    if (!visited[i])
      topologicalSortUtil(i, V);
  result.push(s);
}

void addEdge(int from, int to) {
  adj[from].push_back(to);
}

#pragma clang diagnostic pop