#pragma once

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <tuple>
#include <vector>

struct position {
  int x;
  int y;
};

class cell {

public:
  enum cell_state { DEAD, ALIVE };
  cell_state curr_state;
  cell_state next_state;
  position cell_position;

  void set_state(bool const &state);
  cell wrap_cell(int const &x, int const &y);
};
