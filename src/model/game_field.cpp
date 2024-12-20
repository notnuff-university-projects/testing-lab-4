#include <matrices/matrix.h>

#include "game_field.h"
#include "cell.h"

namespace tetris_model {

GameField::GameField(int rows, int cols)
  : rows_(rows), cols_(cols) {

  cells_ = Matrix<CellState>(rows, cols);

}

int GameField::Rows() const { return rows_; }

int GameField::Cols() const { return cols_; }

void GameField::SetCellState(int row, int col, CellState state) {
  cells_[row][col] = state;
}

CellState GameField::GetCellState(int row, int col) const {
  return cells_[row][col];
}

std::vector<Cell> GameField::GetCellsByType(CellState state) {
  std::vector<Cell> result;

  for (auto i = 0; i < cells_.Rows(); ++i) {
    for (auto j = 0; j < cells_.Columns(); ++j) {
      if (GetCellState(i, j) != state) continue;

      result.emplace_back(i, j, state);
    }
  }

  return result;
}

bool GameField::IsOutOfBounds(const Cell& cell) const {
  return cells_.IsOutOfBounds(cell.Row, cell.Col);
}

bool GameField::IsCanPlaceCell(const Cell& cell) const {
  if ( IsOutOfBounds(cell) ) return false;

  auto currentState = cells_[cell.Row][cell.Col];
  if ( currentState == CellState::EMPTY ) return true;
  if ( currentState == cell.State) return true;

  return false;
}


}