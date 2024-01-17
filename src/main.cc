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
  grids grids;
  grids._current_grid.init();
  grids._current_grid.set_start_condition();

  grids._next_grid.init();

  grids._current_grid.draw();
  grids.execute();
  return 0;
}

// start position:
// row col
// 7   8
// 8   9
// 9   7
// 9   8
// 9   9