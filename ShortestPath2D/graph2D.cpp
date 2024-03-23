#include "graph2D.h"
#include <queue>

using std::queue;

graph2D::graph2D(int width, int height) : width(width), height(height) {
  surrounded = new bool *[height];
  for (int i = 0; i < height; i++)
    surrounded[i] = new bool[width]{false};
}

void graph2D::addBarrier(int sx, int sy, int ex, int ey) {
  for (int y = sy; y <= ey; y++)
    for (int x = sx; x <= ex; x++)
      surrounded[y][x] = true;
}

graph2D::~graph2D() {
  for (int i = 0; i < height; i++)
    delete[] surrounded[i];
  delete[] surrounded;
}

int graph2D::bfs(point s, point e) const {
  auto visited = new bool *[height];
  auto parent = new point *[height];
  for (int i = 0; i < height; i++) {
    parent[i] = new point[width];
    visited[i] = new bool[width]{false};
  }
  queue<point> q;
  visited[s.y][s.x] = true;
  parent[s.y][s.x] = {-1, -1};
  q.push(s);
  auto visit = [&parent, this, &visited, &q, &s](point start) {
      if (!visited[start.y][start.x] && !surrounded[start.y][start.x]) {
        visited[start.y][start.x] = true;
        parent[start.y][start.x] = s;
        q.push(start);
      }
  };
  while (!q.empty()) {
    s = q.front();
    if (s == e)break;
    q.pop();
    if (s.x > 0)
      visit({s.x - 1, s.y});
    if (s.x + 1 < width)
      visit({s.x + 1, s.y});
    if (s.y > 0)
      visit({s.x, s.y - 1});
    if (s.y + 1 < height)
      visit({s.x, s.y + 1});
  }
  int temp = 0;
  if (visited[e.y][e.x]) {
    for (point v = parent[e.y][e.x]; v.x != -1; v = parent[v.y][v.x])
      temp++;
  }
  for (int i = 0; i < height; i++) {
    delete[] visited[i];
    delete[] parent[i];
  }
  delete[] visited;
  delete[] parent;
  return temp;
}

int graph2D::getPath(point s, point e) const {
  return bfs(s, e);
}

bool point::operator==(point &p) const {
  return p.x == x && p.y == y;
}
