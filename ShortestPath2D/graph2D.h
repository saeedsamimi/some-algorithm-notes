#ifndef QUERA_GRAPH2D_H
#define QUERA_GRAPH2D_H

#include <vector>
#include <set>
#include <string>

using namespace std;

struct point {
  int x = 0, y = 0;
  
  bool operator ==(point &p) const;
};

class graph2D {
public:
  // Constructors
  graph2D(int width, int height);
  
  // Destructor
  ~graph2D();
  
  // Functions
  void addBarrier(int, int, int, int);
  [[nodiscard]]
  int getPath(point s, point e) const;
private:
  const int width, height;
  bool **surrounded;
  
  // Utils
  [[nodiscard]] int bfs(point,point) const;
};


#endif //QUERA_GRAPH2D_H
