#include "grid.h"
#include "cell.h"
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <thread>
#include <tuple>
#include <vector>

void grid::set_size() {
  _grid.resize(_y, std::vector<cell>(_x));
  _next_grid.resize(_y, std::vector<cell>(_x));
}

std::string state_symbol(bool state) {
  return state ? "\033[1;34mX\033[0m" : " ";
}

void grid::draw(int const &generations) {

  std::cout << "Generations: " << generations << std::endl;
  int col_counter = 0;
  std::string grid_head;
  for (auto const &cell : _grid.at(0)) {
    if (col_counter == 0) {
      grid_head = grid_head + "\033[1;31m" + std::to_string(col_counter) +
                  "\033[0m" + ".";
    } else {
      grid_head = grid_head + std::to_string(col_counter) + ".";
    }
    col_counter++;
    if (col_counter == 10) {
      col_counter = 0;
    }
  }
  std::cout << " " << grid_head << std::endl;
  int rows = 0;
  for (auto const &row : _grid) {
    col_counter = 0;
    for (auto const &col : row) {
      // if (col_counter == 0) {
      // std::cout << rows << ;
      // }
      if (&col != &row.back()) {

        if (col.curr_state == cell::ALIVE) {
          std::cout << "|" << state_symbol(true);
        }
        if (col.curr_state == cell::DEAD) {
          std::cout << "|" << state_symbol(false);
        }
      } else {
        if (col.curr_state == cell::ALIVE) {
          std::cout << "|" << state_symbol(true);
        }
        if (col.curr_state == cell::DEAD) {
          std::cout << "|" << state_symbol(false);
        }
        std::cout << "|" << rows << "\n";
      }
      col_counter++;
    }
    rows++;
  }
  std::cout << " " << grid_head << std::endl;
}

void cell::set_state(bool const &state) {
  state ? curr_state = cell::ALIVE : curr_state = cell::DEAD;
}
void grid::init(std::vector<std::vector<cell>> &grid) {

  _x = 65;
  _y = 30;
  set_size();

  int rows = 0;
  for (auto &row : grid) {
    int cols = 0;
    for (auto &cell : row) {
      cell.set_state(false);
      cell.cell_position.x = cols;
      cell.cell_position.y = rows;
      cols++;
    }
    rows++;
  }
}

void grid::square(int const &x, int const &y) {
  // start in the down left corner
  set_cell_state(x, y, true);
  set_cell_state(x + 1, y, true);
  set_cell_state(x, y + 1, true);
  set_cell_state(x + 1, y + 1, true);
}

void grid::diamond() {
  // set_cell_state(_grid.at(11).at(25), true);
  // set_cell_state(_grid.at(11).at(26), true);
  // set_cell_state(_grid.at(11).at(27), true);
  // set_cell_state(_grid.at(11).at(28), true);
  // set_cell_state(_grid.at(13).at(23), true);
  // set_cell_state(_grid.at(13).at(24), true);
  // set_cell_state(_grid.at(13).at(25), true);
  // set_cell_state(_grid.at(13).at(26), true);
  // set_cell_state(_grid.at(13).at(27), true);
  // set_cell_state(_grid.at(13).at(28), true);
  // set_cell_state(_grid.at(13).at(29), true);
  // set_cell_state(_grid.at(13).at(30), true);
  // set_cell_state(_grid.at(15).at(21), true);
  // set_cell_state(_grid.at(15).at(22), true);
  // set_cell_state(_grid.at(15).at(23), true);
  // set_cell_state(_grid.at(15).at(24), true);
  // set_cell_state(_grid.at(15).at(25), true);
  // set_cell_state(_grid.at(15).at(26), true);
  // set_cell_state(_grid.at(15).at(27), true);
  // set_cell_state(_grid.at(15).at(28), true);
  // set_cell_state(_grid.at(15).at(29), true);
  // set_cell_state(_grid.at(15).at(30), true);
  // set_cell_state(_grid.at(15).at(31), true);
  // set_cell_state(_grid.at(15).at(32), true);
  // set_cell_state(_grid.at(17).at(23), true);
  // set_cell_state(_grid.at(17).at(24), true);
  // set_cell_state(_grid.at(17).at(25), true);
  // set_cell_state(_grid.at(17).at(26), true);
  // set_cell_state(_grid.at(17).at(27), true);
  // set_cell_state(_grid.at(17).at(28), true);
  // set_cell_state(_grid.at(17).at(29), true);
  // set_cell_state(_grid.at(17).at(30), true);
  // set_cell_state(_grid.at(19).at(25), true);
  // set_cell_state(_grid.at(19).at(26), true);
  // set_cell_state(_grid.at(19).at(27), true);
  // set_cell_state(_grid.at(19).at(28), true);
}

void grid::glider_gun() {
  square(20, 9);
  square(54, 7);
  set_cell_state(30, 10, true);
  set_cell_state(30, 11, true);
  set_cell_state(30, 9, true);

  set_cell_state(31, 8, true);
  set_cell_state(32, 7, true);
  set_cell_state(33, 7, true);

  set_cell_state(31, 12, true);
  set_cell_state(32, 13, true);
  set_cell_state(33, 13, true);

  set_cell_state(34, 10, true);

  set_cell_state(35, 8, true);
  set_cell_state(36, 9, true);
  set_cell_state(36, 10, true);
  set_cell_state(37, 10, true);
  set_cell_state(36, 11, true);
  set_cell_state(35, 12, true);

  set_cell_state(40, 9, true);
  set_cell_state(41, 9, true);
  set_cell_state(40, 8, true);
  set_cell_state(41, 8, true);
  set_cell_state(40, 7, true);
  set_cell_state(41, 7, true);
  set_cell_state(42, 6, true);
  set_cell_state(42, 10, true);

  set_cell_state(44, 6, true);
  set_cell_state(44, 5, true);

  set_cell_state(44, 11, true);
  set_cell_state(44, 12, true);

  set_cell_state(43, 16, true);
  set_cell_state(44, 16, true);
  set_cell_state(43, 17, true);
  set_cell_state(44, 18, true);
  set_cell_state(45, 18, true);
  set_cell_state(46, 18, true);
  set_cell_state(46, 19, true);
}
void grid::set_start_condition() {
  int x = 0;

  for (int i = 0; i < 10; i++) {
    switch (i) {
    case 0:
      x = 8;
      break;
    case 1:
      x = 15;
      break;
    case 2:
      x = 1;
      break;
    case 3:
      x = 25;
      break;
    case 4:
      x = 12;
      break;
    }
    int y = x - 1;
    set_cell_state(y, x, true);
    set_cell_state(y + 1, x + 1, true);
    set_cell_state(y + 2, x - 1, true);
    set_cell_state(y + 2, x, true);
    set_cell_state(y + 2, x + 1, true);
  }
}

void grid::set_cell_state(int const &x, int const &y, bool const &state) {
  int x_wrapped;
  int y_wrapped;
  x_wrapped = (x + _x) % _x;
  y_wrapped = (y + _y) % _y;

  _grid.at(y_wrapped).at(x_wrapped).set_state(state);
}

cell::cell_state grid::get_neighbor_cell_state(int const &x, int const &y) {
  int x_size = _grid.at(0).size();
  int y_size = _grid.size();

  return (_grid.at((y_size + y) % y_size).at((x_size + x) % x_size).curr_state);
}
int grid::set_neighbors(int const &x, int const &y) {
  int living_cell_neighbors = 0;

  if (get_neighbor_cell_state(x - 1, y) == cell::ALIVE) {
    living_cell_neighbors++;
  }
  if (get_neighbor_cell_state(x + 1, y) == cell::ALIVE) {
    living_cell_neighbors++;
  }
  if (get_neighbor_cell_state(x - 1, y - 1) == cell::ALIVE) {
    living_cell_neighbors++;
  }
  if (get_neighbor_cell_state(x, y - 1) == cell::ALIVE) {
    living_cell_neighbors++;
  }
  if (get_neighbor_cell_state(x + 1, y - 1) == cell::ALIVE) {
    living_cell_neighbors++;
  }
  if (get_neighbor_cell_state(x + 1, y + 1) == cell::ALIVE) {
    living_cell_neighbors++;
  }
  if (get_neighbor_cell_state(x, y + 1) == cell::ALIVE) {
    living_cell_neighbors++;
  }
  if (get_neighbor_cell_state(x - 1, y + 1) == cell::ALIVE) {
    living_cell_neighbors++;
  }
  return living_cell_neighbors;
}

void grid::game_play(int const &generations) {
  int rows = 0;
  for (auto &row : _grid) {
    int cols = 0;
    for (auto &cell : row) {

      int n_num = set_neighbors(cols, rows);
      if (cell.curr_state == cell::DEAD) {
        if (n_num == 3) {
          // become alive
          _next_grid.at(rows).at(cols).curr_state = cell::ALIVE;
        } else {
          _next_grid.at(rows).at(cols).curr_state = cell::DEAD;
        }
      } else if (cell.curr_state == cell::ALIVE) {
        if (n_num < 2) {
          // die due to loneliness
          _next_grid.at(rows).at(cols).curr_state = cell::DEAD;
        } else if (n_num == 2 or n_num == 3)
          // keep stable
          _next_grid.at(rows).at(cols).curr_state = cell::ALIVE;
      } else if (n_num > 4) {
        // overpopulation
        _next_grid.at(rows).at(cols).curr_state = cell::DEAD;
      }

      cols++;
    }
    rows++;
  }
  _grid = std::move(_next_grid);

  init(_next_grid);
  draw(generations);
}

void grid::execute() {
  int generations = 0;
  draw(generations);
  std::cin.get();
  while (true) {
    //  draw();
    //  std::cin.get();
    grid::game_play(generations);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    system("clear");
    generations++;
  }
}