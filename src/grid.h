#pragma once
#include "cell.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <tuple>
#include <vector>

class grid {
public:
  int _y;
  int _x;

  void draw(int const &generations);
  void set_prev_cell_state();
  void fill_neighbors_vec_for_counting();
  void init(std::vector<std::vector<cell>> &grid);
  void set_size();
  void set_start_condition();
  void set_cell_state(int const &x, int const &y, bool const &state);
  int set_neighbors(int const &x, int const &y);
  void square(int const &x, int const &y);
  void diamond();
  void glider_gun();
  void fill2();
  void set_cell_neighbor_states(cell &cell, int x_counter, int y_counter);
  void game_play(int const &generations);
  void execute();
  cell::cell_state get_neighbor_cell_state(int const &x, int const &y);

  std::vector<std::vector<cell>> _grid;
  std::vector<std::vector<cell>> _next_grid;
};
