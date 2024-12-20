#ifndef GAME_FIELD_H
#define GAME_FIELD_H

#include <vector>
#include <matrices/matrix.h>

#include "cell.h"

namespace tetris_model {

class GameField {
public:
  GameField(int rows, int cols);
  virtual ~GameField() = default;

public:
  int Rows() const;
  int Cols() const;

  virtual void SetCellState(int row, int col, CellState state);
  virtual CellState GetCellState(int row, int col) const;

public:
  std::vector<Cell> GetCellsByType(CellState state);
  bool IsOutOfBounds(const Cell& cell) const;
  bool IsCanPlaceCell(const Cell& cell) const;

protected:
  int rows_;
  int cols_;

  Matrix<CellState> cells_;
};

}


#endif //GAME_FIELD_H
