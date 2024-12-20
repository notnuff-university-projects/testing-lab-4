#include "game_field_common.h"

std::shared_ptr<GameField> CreateGameField(std::initializer_list<std::initializer_list<CellState>> matrix) {
  auto rows = matrix.size();
  if (rows == 0) return nullptr;
  auto cols = matrix.begin()->size();

  auto field = std::make_shared<tetris_model::GameField>(rows, cols);

  int i = 0;
  for(const auto& cell_rows : matrix) {
    int j = 0;
    for(const auto& cell : cell_rows) {
      field->SetCellState(i, j, cell);
      ++j;
    }
    ++i;
  }

  return field;
}

bool AreFieldsEqual(const std::shared_ptr<GameField>& gf1,
  const std::shared_ptr<GameField>& gf2)  {

  if (gf1->Cols() != gf2->Cols()) return false;
  if (gf1->Rows() != gf2->Rows()) return false;

  for (int i = 0; i < gf1->Rows(); ++i) {
    for (int j = 0; j < gf1->Cols(); ++j) {
      if (gf1->GetCellState(i, j) != gf2->GetCellState(i, j)) return false;
    }
  }

  return true;
}
