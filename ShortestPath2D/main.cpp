#include <iostream>

#include "graph2D.h"

int main() {
  graph2D g(11, 10);
  g.addBarrier(3, 2, 5, 4);
  g.addBarrier(0, 6, 3, 7);
  g.addBarrier(7, 0, 9, 6);
  cout << "Path from (0,0) to (10,11) length is: "
       << g.getPath({0, 0}, {10, 9});
  return 0;
}
