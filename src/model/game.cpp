#include "game.h"

#include <vector>
#include <exceptions/exceptions.h>

#include "cell.h"

namespace tetris_model {


Game::Game(const std::shared_ptr<GameField>& init_field) {
  if (init_field == nullptr) {
    throw init_error("Game:: init_field cannot be nullptr");
  }
  if (init_field->Cols() == 0 || init_field->Rows() == 0) {
    throw init_error("Game:: init_field cannot be empty");
  }
  field_ = init_field;
}

void Game::Run() {
  int deltaX = 0, deltaY = 1;

  while ( IsCanMoveFigure(deltaY, deltaX) ) {
    MoveFigure(deltaY, deltaX);
  }

}

std::shared_ptr<GameField> Game::GetField() const {
  return field_;
}

bool Game::IsCanMoveFigure(int dRow, int dCol) {
  std::vector<Cell> figure = field_->GetCellsByType(CellState::FIGURE);
  if ( figure.empty() ) return false;

  GetMovedFigure(figure, dRow, dCol);

  for(const Cell& cell : figure) {
    if (!field_->IsCanPlaceCell(cell)) return false;
  }

  return true;
}

void Game::MoveFigure(int dRow, int dCol) {
  std::vector<Cell> figure = field_->GetCellsByType(CellState::FIGURE);

  for(const Cell& cell : figure) {
    field_->SetCellState(cell.Row, cell.Col, CellState::EMPTY);
  }

  GetMovedFigure(figure, dRow, dCol);

  for(const Cell& cell : figure) {
    field_->SetCellState(cell.Row, cell.Col, CellState::FIGURE);
  }
}

void Game::GetMovedFigure(std::vector<Cell>& in_outFigure, int dRow, int dCol) {
  for(Cell& cell : in_outFigure) {
    cell.Row += dRow;
    cell.Col += dCol;
  }
}


}