#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"

#include <bits/stdc++.h>

using namespace std;

const int maxn = 100;
vector<int> adj[maxn];
int Data[maxn];
bool visited[maxn];

void addEdge(int, int);
void countComponents(int);

int main() {
  fstream in("test.txt");
  cin.rdbuf(in.rdbuf());
  int V, E;
  cin >> V >> E;
  for (int i = 0; i < E; ++i) {
    int u, v;
    cin >> u >> v;
    addEdge(u-1, v-1);
  }
  countComponents(V);
  return 0;
}

void addEdge(int u, int v) {
  adj[u].push_back(v);
  adj[v].push_back(u);
}

void dfs(int s, int count) {
  visited[s] = true;
  Data[s] = count;
  for (int num: adj[s])
    if (!visited[num])
      dfs(num, count);
}

void countComponents(int V) {
  memset(visited, 0, sizeof visited);
  int count = 0;
  for (int i = 0; i < V; i++) {
    if (!visited[i]) {
      dfs(i, count);
      count++;
    }
  }
  cout << "Count of components is: " << count << endl;
  cout << "The color(data) of the components: \n";
  for(int i = 0;i<V;i++)
    cout << Data[i];
  cout << endl;
}

#pragma clang diagnostic pop