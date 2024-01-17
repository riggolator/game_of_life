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

class cell {

public:
  enum cell_state { INVALID, DEAD, ALIVE };
  cell_state curr_state;
  cell_state next_state;

  cell_state neighbor_ul_state;
  cell_state neighbor_um_state;
  cell_state neighbor_ur_state;
  cell_state neighbor_ml_state;
  cell_state neighbor_mr_state;
  cell_state neighbor_dl_state;
  cell_state neighbor_dm_state;
  cell_state neighbor_dr_state;

  std::vector<cell_state> neighbors;
  // cell() : curr_state(ALIVE) {}
};