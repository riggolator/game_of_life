#include "cell.h"
#include "grid.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

int main() {
  grid grid;
  grid.init(grid._grid);
  grid.init(grid._next_grid);
  // grids._current_grid.square();
  grid.diamond();
  grid.glider_gun();
  grid.set_start_condition();

  // grids._next_grid.init();

  //  grids._current_grid.draw();
  grid.execute();
  return 0;
}

// start position:
// row col
// 7   8
// 8   9
// 9   7
// 9   8
// 9   9