#ifndef CELL__H_
#define CELL__H_

#include <utility>

class Cell {
public:
  std::pair<int, int> parent;
  double f, g, h;
  Cell() : parent(-1, -1), f(-1), g(-1), h(-1) {}
};
#endif
