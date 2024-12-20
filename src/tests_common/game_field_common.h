#ifndef GAME_FIELD_COMMON_H
#define GAME_FIELD_COMMON_H
#include <memory>

#include "../model/game_field.h"

using namespace tetris_model;


const auto E = CellState::EMPTY;
const auto G = CellState::FIGURE;
const auto L = CellState::LANDSCAPE;

std::shared_ptr<GameField> CreateGameField(std::initializer_list<std::initializer_list<CellState>> matrix);

bool AreFieldsEqual(const std::shared_ptr<GameField>& gf1, const std::shared_ptr<GameField>& gf2);


#endif //GAME_FIELD_COMMON_H
