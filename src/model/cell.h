#ifndef CELL_H
#define CELL_H

namespace tetris_model {

enum class CellState {
  EMPTY = 0,
  FIGURE = 1,
  LANDSCAPE = 2,
};

struct Cell {
  int Row;
  int Col;
  CellState State;
};

}
#endif //CELL_H
