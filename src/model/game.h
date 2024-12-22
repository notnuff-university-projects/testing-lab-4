#ifndef GAME_H
#define GAME_H
#include <memory>
#include <vector>

#include "game_field.h"


namespace tetris_model {

class Game {
public:
  explicit Game(const std::shared_ptr<GameField>& init_field);
  virtual ~Game() = default;

public:
  virtual void Run();
  virtual bool IsCanMakeStep();
  virtual void MakeStep();
  virtual std::shared_ptr<GameField> GetField() const;

protected:
  bool IsCanMoveFigure(int dRow, int dCol);
  void MoveFigure(int dRow, int dCol);

  void GetMovedFigure(std::vector<Cell>& in_outFigure, int dRow, int dCol);

protected:
  std::shared_ptr<GameField> field_ = nullptr;

};

}

#endif //GAME_H
