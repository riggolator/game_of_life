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
  int _rows;
  int _cols;

  // std::vector<std::vector<cell>> _grid;

  void set_size();
  std::vector<std::tuple<std::string, int>> get_size();
  void draw();
  void init();
  void set_cell_state(cell &cell, bool state);
  void set_prev_cell_state();
  void fill_neighbors_vec_for_counting();
  // void game_play();
  // void execute();
  void square();
  void set_start_condition();
  std::vector<std::vector<cell>> _grid;
};

class grids {
public:
  grid _next_grid;
  grid _current_grid;
  void game_play();
  void execute();
};