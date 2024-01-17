#include "grid.h"
#include "cell.h"
#include <algorithm>
#include <cstdlib>
// #include <ctime>
#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <thread>
#include <tuple>
#include <vector>

void grid::set_size() {
  _grid.resize(_cols, std::vector<cell>(_rows));
  // std::cout << "size set" << std::endl;
}

std::vector<std::tuple<std::string, int>> grid::get_size() {
  int cols = _grid.size();
  int rows = _grid.at(0).size();
  std::vector<std::tuple<std::string, int>> vals;
  // vals.push_back(std::tuple<std::string, int>{"cols", cols});
  // vals.push_back(std::tuple<std::string, int>{"rows", rows});
  return vals;
}
std::string state_symbol(bool state) { return state ? "X" : " "; }

void grid::draw() {

  // system("clear");
  std::cout << "Welcome to Conway's game of life!" << std::endl;
  std::cout << " 0.1.2.3.4.5.6.7.8.9.0.1.2.3.4.5.6.7.8.9" << std::endl;
  int rows = 0;
  for (auto const &row : _grid) {
    for (auto const &col : row) {
      if (&col != &row.back()) {

        if (col.curr_state == cell::ALIVE) {
          std::cout << "|" << state_symbol(true);
        }
        if (col.curr_state == cell::DEAD) {
          std::cout << "|" << state_symbol(false);
        } // else if (col.curr_state == cell::INVALID) {
          // return;
        //}
      } else {
        std::cout << "| " << rows << "\n";
      }
    }
    rows++;
  }
}

void grid::set_cell_state(cell &cell, bool state) {
  state ? cell.curr_state = cell::ALIVE : cell.curr_state = cell::DEAD;
  // std::cout << "cell state set to :" << state << std::endl;
}
void grid::init() {

  _cols = 20;
  _rows = 20;
  set_size();
  int rows = 0;
  for (auto &row : _grid) {
    int cols = 0;
    for (auto &cell : row) {
      set_cell_state(cell, false);

      // std::cout << "zeile: " << rows << " spalte:" << cols
      //           << " state: " << cell.curr_state << std::endl;
      cols++;
    }
    rows++;
  }
}
void grid::set_start_condition() {
  set_cell_state(_grid.at(7).at(8), true);
  set_cell_state(_grid.at(8).at(9), true);
  set_cell_state(_grid.at(9).at(7), true);
  set_cell_state(_grid.at(9).at(8), true);
  set_cell_state(_grid.at(9).at(9), true);

  // set_neighbors();
}
void grid::set_prev_cell_state() {}

void grid::fill_neighbors_vec_for_counting() {
  int rows = 0;
  for (auto &row : _grid) {
    int cols = 0;
    //  std::cout << "rows: " << rows << std::endl;
    for (auto &cell : row) {
      //  std::cout << "cols: " << cols << std::endl;
      // Ecke oben links
      if (rows == 0 and cols == 0) {
        //    std::cout << "Ecke iben links" << std::endl;
        cell.neighbor_ul_state = cell::INVALID;
        cell.neighbor_um_state = cell::INVALID;
        cell.neighbor_ur_state = cell::INVALID;
        cell.neighbor_ml_state = cell::INVALID;
        cell.neighbor_dl_state = cell::INVALID;
        //  std::cout << "check1" << std::endl;
        cell.neighbor_mr_state = _grid[rows][cols + 1].curr_state;
        cell.neighbor_dr_state = _grid[rows + 1][cols + 1].curr_state;
        cell.neighbor_dm_state = _grid[rows + 1][cols].curr_state;
        // std::cout << "check2" << std::endl;

      }
      // obere Kante
      else if (rows == 0 and cols != 0 and &cell != &row.back()) {
        // else if (rows == 0 and cols > 0 and cols < 20) {
        //        std::cout << "Oberkante row: " << rows << std::endl;
        //       std::cout << "Oberkante cols: " << cols << std::endl;
        //      std::cout << "Oberkante" << std::endl;
        cell.neighbor_ul_state = cell::INVALID;
        cell.neighbor_um_state = cell::INVALID;
        //    std::cout << "check3" << std::endl;
        cell.neighbor_ur_state = cell::INVALID;
        //  std::cout << "check4" << std::endl;
        cell.neighbor_ml_state = _grid[rows][cols - 1].curr_state;
        cell.neighbor_mr_state = _grid[rows][cols + 1].curr_state;
        cell.neighbor_dl_state = _grid[rows + 1][cols - 1].curr_state;
        cell.neighbor_dm_state = _grid[rows + 1][cols].curr_state;
        cell.neighbor_dr_state = _grid[rows + 1][cols + 1].curr_state;
      }
      // rechte Ecke
      else if (rows == 0 and &cell == &row.back()) {
        cell.neighbor_ul_state = cell::INVALID;
        cell.neighbor_um_state = cell::INVALID;
        cell.neighbor_ur_state = cell::INVALID;
        cell.neighbor_ml_state = _grid[rows][cols - 1].curr_state;
        cell.neighbor_mr_state = cell::INVALID;
        cell.neighbor_dl_state = _grid[rows + 1][cols - 1].curr_state;
        cell.neighbor_dm_state = _grid[rows + 1][cols].curr_state;
        cell.neighbor_dr_state = cell::INVALID;

      }

      // rechte Kante
      else if (&cell == &row.back() and rows != 0 and &row != &_grid.back()) {
        //        std::cout << "rechte kante" << std::endl;
        cell.neighbor_ul_state = _grid[rows - 1][cols - 1].curr_state;
        cell.neighbor_um_state = _grid[rows - 1][cols].curr_state;
        cell.neighbor_ur_state = cell::INVALID;
        cell.neighbor_ml_state = _grid[rows][cols - 1].curr_state;
        cell.neighbor_mr_state = cell::INVALID;
        cell.neighbor_dl_state = _grid[rows + 1][cols - 1].curr_state;
        cell.neighbor_dm_state = _grid[rows + 1][cols].curr_state;
        cell.neighbor_dr_state = cell::INVALID;

      }
      // ecke unten rechts
      else if (&cell == &row.back() and &row == &_grid.back()) {

        cell.neighbor_ul_state = _grid[rows - 1][cols - 1].curr_state;
        cell.neighbor_um_state = _grid[rows - 1][cols].curr_state;
        cell.neighbor_ur_state = cell::INVALID;
        cell.neighbor_ml_state = _grid[rows][cols - 1].curr_state;
        cell.neighbor_mr_state = cell::INVALID;
        cell.neighbor_dl_state = cell::INVALID;
        cell.neighbor_dm_state = cell::INVALID;
        cell.neighbor_dr_state = cell::INVALID;
      }
      // untere Kante
      else if (&cell != &row.back() and cols != 0 and &row == &_grid.back()) {

        cell.neighbor_ul_state = _grid[rows - 1][cols - 1].curr_state;
        cell.neighbor_um_state = _grid[rows - 1][cols].curr_state;
        cell.neighbor_ur_state = _grid[rows - 1][cols + 1].curr_state;
        cell.neighbor_ml_state = _grid[rows][cols - 1].curr_state;
        cell.neighbor_mr_state = _grid[rows][cols + 1].curr_state;
        cell.neighbor_dl_state = cell::INVALID;
        cell.neighbor_dm_state = cell::INVALID;
        cell.neighbor_dr_state = cell::INVALID;

      }

      // ecke unten links
      else if (cols == 0 and &row == &_grid.back()) {

        cell.neighbor_ul_state = cell::INVALID;
        cell.neighbor_um_state = _grid[rows - 1][cols].curr_state;
        cell.neighbor_ur_state = _grid[rows - 1][cols + 1].curr_state;
        cell.neighbor_ml_state = cell::INVALID;
        cell.neighbor_mr_state = _grid[rows][cols + 1].curr_state;
        cell.neighbor_dl_state = cell::INVALID;
        cell.neighbor_dm_state = cell::INVALID;
        cell.neighbor_dr_state = cell::INVALID;
      }

      // kante links

      else if (cols == 0 and &row != &_grid.back() and rows != 0) {

        cell.neighbor_ul_state = cell::INVALID;
        cell.neighbor_um_state = _grid[rows - 1][cols].curr_state;
        cell.neighbor_ur_state = _grid[rows - 1][cols + 1].curr_state;
        cell.neighbor_ml_state = cell::INVALID;
        cell.neighbor_mr_state = _grid[rows][cols + 1].curr_state;
        cell.neighbor_dl_state = cell::INVALID;
        cell.neighbor_dm_state = _grid[rows + 1][cols].curr_state;
        cell.neighbor_dr_state = _grid[rows + 1][cols + 1].curr_state;
      }

      // alles dazwischen
      else {

        cell.neighbor_ul_state = _grid[rows - 1][cols - 1].curr_state;
        cell.neighbor_um_state = _grid[rows - 1][cols].curr_state;
        cell.neighbor_ur_state = _grid[rows - 1][cols + 1].curr_state;
        cell.neighbor_ml_state = _grid[rows][cols - 1].curr_state;
        cell.neighbor_mr_state = _grid[rows][cols + 1].curr_state;
        cell.neighbor_dl_state = _grid[rows + 1][cols - 1].curr_state;
        cell.neighbor_dm_state = _grid[rows + 1][cols].curr_state;
        cell.neighbor_dr_state = _grid[rows + 1][cols + 1].curr_state;
      }
      cell.neighbors.push_back(cell.neighbor_ul_state);
      cell.neighbors.push_back(cell.neighbor_um_state);
      cell.neighbors.push_back(cell.neighbor_ur_state);
      cell.neighbors.push_back(cell.neighbor_ml_state);
      cell.neighbors.push_back(cell.neighbor_mr_state);
      cell.neighbors.push_back(cell.neighbor_dl_state);
      cell.neighbors.push_back(cell.neighbor_dm_state);
      cell.neighbors.push_back(cell.neighbor_dr_state);
      cols++;
    }
    rows++;
  }
}

// irgendeine std::ranges funktion ?
int check_neighbors(cell const &cell) {
  int n_num = 0;
  for (auto const &cs : cell.neighbors) {
    if (cs == cell::ALIVE) {
      n_num++;
    }
  }
  return n_num;
}

void grids::game_play() {
  int rows = 0;
  for (auto &row : _current_grid._grid) {
    int cols = 0;
    for (auto &cell : row) {
      //      if (cell.curr_state == cell::DEAD) {

      int n_num = check_neighbors(cell);
      // std::cout << "zeile: " << rows << " spalte: " << cols
      //           << " neighbors: " << n_num << std::endl;
      if (cell.curr_state == cell::DEAD) {
        if (n_num == 3) {
          // zum Leben erwecken
          _next_grid._grid.at(rows).at(cols).curr_state = cell::ALIVE;
        } else {
          _next_grid._grid.at(rows).at(cols).curr_state = cell::DEAD;
        }
      } else if (cell.curr_state == cell::ALIVE) {
        if (n_num < 2) {
          // Einsamkeit
          _next_grid._grid.at(rows).at(cols).curr_state = cell::DEAD;
        } else if (n_num == 2 or n_num == 3)
          // stabile bleiben
          _next_grid._grid.at(rows).at(cols).curr_state = cell::ALIVE;
        // continue;
      } else if (n_num > 4) {
        // Überbevölkerung
        _next_grid._grid.at(rows).at(cols).curr_state = cell::DEAD;
      }

      // if (_next_grid._grid.at(rows).at(cols).curr_state == cell::ALIVE) {
      // std::cout << cell.neighbor_dl_state << std::endl;
      // std::cout << "x: " << cols << " y: " << rows << " neighbors: \n"
      //<< "down left:\t" << cell.neighbor_dl_state << "\n"
      //<< "down right:\t" << cell.neighbor_dr_state << "\n"
      //<< "down middle:\t" << cell.neighbor_dm_state << "\n"
      //<< "right:\t\t" << cell.neighbor_mr_state << "\n"
      //<< "up right:\t" << cell.neighbor_ur_state << "\n"
      //<< "up middle:\t" << cell.neighbor_um_state << "\n"
      //<< "up left:\t" << cell.neighbor_ul_state << "\n"
      //<< "middle left:\t" << cell.neighbor_ml_state << "\n"
      //<< std::endl;
      //}
      cell.neighbors.clear();
      cols++;
    }
    rows++;
  }
  _current_grid = std::move(_next_grid);

  _next_grid.init();
  _current_grid.draw();
}

void grids::execute() {

  _current_grid.fill_neighbors_vec_for_counting();
  _current_grid.draw();
  while (true) {
    // std::cin.get();
    grids::game_play();
    _current_grid.fill_neighbors_vec_for_counting();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    system("clear");
  }
}