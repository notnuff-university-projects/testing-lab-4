#include <exceptions/exceptions.h>

#include "tetris_controller.h"


namespace tetris_controller {

void TetrisController::SetIOInterface(const std::shared_ptr<Game_IO_I>& io_interface) {
  io_ = io_interface;
}

void TetrisController::SetGameModel(const std::shared_ptr<Game>& game) {
  game_model_ = game;
}

void TetrisController::GameInitFromIO() {
  auto input_str = io_->Read();
  auto game_field = ParceStringToGameField(input_str);
  SetGameModel(std::make_shared<Game>(game_field));
}

void TetrisController::GameSimulate() {
  game_model_->Run();
}

void TetrisController::GamePrint() {
  auto output_str = ParceGameFieldToString( game_model_->GetField() );
  io_->Write(output_str);
}

std::shared_ptr<GameField> TetrisController::ParceStringToGameField(
    const std::string& input_str) {

  std::string error_base = "TetrisController::ParceStringToGameField: ";
  if (input_str.empty()) {
    throw parse_error(error_base + "empty string");
  }

  std::stringstream str_stream(input_str);
  int rows, cols;

  std::string current_line;
  std::getline(str_stream, current_line);

  if ( !( std::stringstream(current_line) >> rows >> cols) ) {
    throw parse_error(error_base + "invalid dimensions");
  }

  auto game_field = std::make_shared<GameField>(rows, cols);

  for (int i = 0; i < rows; ++i) {
    if( !std::getline(str_stream, current_line) )
      throw parse_error(error_base + "rows not matching");

    auto line_cols = static_cast<int>(current_line.size());

    if (line_cols != cols)
      throw parse_error(error_base + "columns not matching");

    for (int j = 0; j < line_cols; ++j) {
      switch (current_line[j]) {
        case '.':
          game_field->SetCellState(i, j, CellState::EMPTY);
        break;
        case '#':
          game_field->SetCellState(i, j, CellState::LANDSCAPE);
        break;
        case 'p':
          game_field->SetCellState(i, j, CellState::FIGURE);
        break;
        default:
          throw parse_error("TetrisController::ParceStringToGameField: unknown character");
      }
    }
  }

  return game_field;
}


std::string TetrisController::ParceGameFieldToString(
    const std::shared_ptr<GameField>& input_field) {

  if (!input_field) {
    throw parse_error("TetrisController::ParceGameFieldToString: input_field is null");
  }

  std::ostringstream output_stream;

  for (int i = 0; i < input_field->Rows(); ++i) {
    for (int j = 0; j < input_field->Cols(); ++j) {
      CellState state = input_field->GetCellState(i, j);
      char cell_char;

      switch (state) {
        case CellState::EMPTY:
          cell_char = '.';
        break;
        case CellState::LANDSCAPE:
          cell_char = '#';
        break;
        case CellState::FIGURE:
          cell_char = 'p';
        break;
        default:
          throw parse_error("TetrisController::ParceGameFieldToString: Unknown CellState encountered");
      }

      output_stream << cell_char;
    }
    output_stream << "\n";
  }

  return output_stream.str();
}



}
