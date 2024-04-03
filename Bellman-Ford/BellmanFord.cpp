#include <limits>
#include <iostream>

using namespace std;

struct Edge {
  int src, dest, weight;
};

class Graph {
public:
  Graph(int V, int E) : V(V), E(E) {
    edges = new Edge[E];
  }
  
  void setEdge(int index, int from, int to, int weight) {
    edges[index] = {from, to, weight};
  }
  
  friend void BellmanFord(Graph &, int);
  
  ~Graph() {
    delete[] edges;
  }

private:
  int V, E;
  
  struct Edge *edges;
};

void printArr(int dist[], int n) {
  printf("Vertex Distance from Source\n");
  for (int i = 0; i < n; ++i)
    printf("%d \t\t %d\n", i, dist[i]);
}

void BellmanFord(Graph &graph, int src) {
  int V = graph.V;
  int E = graph.E;
  int *dist = new int[V];
  
  for (int i = 0; i < V; i++)
    dist[i] = INT_MAX;
  dist[src] = 0;
  
  for (int i = 1; i <= V - 1; i++) {
    for (int j = 0; j < E; j++) {
      int u = graph.edges[j].src;
      int v = graph.edges[j].dest;
      int weight = graph.edges[j].weight;
      if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
        dist[v] = dist[u] + weight;
    }
  }
  
  for (int i = 0; i < E; i++) {
    int u = graph.edges[i].src;
    int v = graph.edges[i].dest;
    int weight = graph.edges[i].weight;
    if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
      printf("Graph contains negative weight cycle");
      delete[] dist;
      return;
    }
  }
  
  printArr(dist, V);
  delete[] dist;
}

int main() {
  int V = 5;
  int E = 8;
  Graph graph(V, E);
  graph.setEdge(0, 0, 1, -1);
  graph.setEdge(1, 0, 2, 4);
  graph.setEdge(2, 1, 2, 3);
  graph.setEdge(3, 1, 3, 2);
  graph.setEdge(4, 1, 4, 2);
  graph.setEdge(5, 3, 2, 5);
  graph.setEdge(6, 3, 1, 1);
  graph.setEdge(7, 4, 3, -3);
  
  BellmanFord(graph, 0);
  Graph graph2(6, 7);
  graph2.setEdge(0, 0, 1, -1);
  graph2.setEdge(6, 0, 3, -100);
  graph2.setEdge(1, 3, 2, -2);
  graph2.setEdge(2, 2, 3, 4);
  graph2.setEdge(3, 0, 2, 3);
  graph2.setEdge(4, 3, 4, 7);
  graph2.setEdge(5, 3, 5, 5);
  BellmanFord(graph2, 0);
  return 0;
}
