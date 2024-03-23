#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"

#include <bits/stdc++.h>

using namespace std;

class node : vector<int> {
public:
  node() : vector<int>() {}
  
  void addNeigh(int v);
  
  friend class tree;

private:
  int parent = -1;
  int depth = -1;
  
  void set(int depth, int parent);
};

class tree : vector<node> {
public:
  explicit tree(int V) :
          vector<node>(V), visited(new bool[V]{false}) {}
  
  void addEdge(int u, int v);
  
  ~tree() {
    delete[] visited;
  }
  
  void callDFS_max();
  
  void callDFS(int s);
  
  void getShortestPath(int from, int to, vector<int> &path);

private:
  void dfs(int s, int parent, int depth);
  
  int depth(int v);
  int parent(int v);
  
  bool *visited;
};

int main() {
  fstream in("test.txt", ios_base::in);
  ofstream out("out.txt");
  cin.rdbuf(in.rdbuf());
  auto startTime = chrono::high_resolution_clock::now();
  int t;
  cin >> t;
  for (int k = 0; k < t; k++) {
    cout << "Test #" << k + 1 << ":\n";
    out << "## TestCase ##" << k + 1 << endl;
    int V;
    cin >> V;
    tree g(V);
    for (int i = 1; i < V; ++i) {
      int u, v;
      cin >> u >> v;
      u--, v--;
      g.addEdge(u, v);
    }
    g.callDFS_max();
    vector<int> path;
    int q;
    cin >> q;
    out << endl;
    for (int i = 0; i < q; ++i) {
      int u, v;
      cin >> u >> v;
      cout << "Generating: " << i + 1 << " / " << q << endl;
      out << "Question #" << i + 1 << " -> from " << u << " to " << v << ":\t";
      u--, v--;
      g.getShortestPath(u, v, path);
      for (int j: path)
        out << j + 1 << ' ';
      out << endl;
      path.clear();
    }
    out << endl;
  }
  auto endTime = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::microseconds>(endTime - startTime).count();
  cout << "-> Time elapsed: " << duration << "us";
  return 0;
}

void node::addNeigh(int v) {
  push_back(v);
}

void node::set(int d, int p) {
  depth = d;
  parent = p;
}

void tree::addEdge(int u, int v) {
  operator[](v).addNeigh(u);
  operator[](u).addNeigh(v);
}

void tree::dfs(int s, int parent, int depth) {
  visited[s] = true;
  operator[](s).set(depth, parent);
  for (int i: operator[](s))
    if (!visited[i])
      dfs(i, s, depth + 1);
}

void tree::callDFS_max() {
  int Max = 0, maxIndex = -1;
  for (int i = 0; i < size(); i++) {
    int newLen = (int) operator[](i).size();
    if (newLen > Max) {
      Max = newLen;
      maxIndex = i;
    }
  }
  callDFS(maxIndex);
}

void tree::callDFS(int s) {
  dfs(s, -1, 0);
  memset(visited, 0, size());
}

void tree::getShortestPath(int from, int to, vector<int> &path) {
  stack<int> way;
  while (from != to)
    if (depth(from) >= depth(to)) {
      path.push_back(from);
      from = parent(from);
    } else {
      way.push(to);
      to = parent(to);
    }
  path.push_back(from);
  while (!way.empty()) {
    path.push_back(way.top());
    way.pop();
  }
}

int tree::depth(int v) {
  return operator[](v).depth;
}

int tree::parent(int v) {
  return operator[](v).parent;
}

#pragma clang diagnostic pop
