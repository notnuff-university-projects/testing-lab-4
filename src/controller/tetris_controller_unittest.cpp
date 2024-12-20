#include <gtest/gtest.h>
#include <exceptions/exceptions.h>

#include "tetris_controller.h"

using namespace tetris_controller;
using namespace tetris_model;
using namespace tetris_view;

#include "game_field_common.h"

auto minimal_gf = CreateGameField({{E}});
class GameModel_Mock : public Game {
public:
  explicit GameModel_Mock() : Game(minimal_gf) {}

  virtual void Run() override {
    WasRunCalled = true;
  }

  virtual std::shared_ptr<GameField> GetField() const override {
    return Field;
  }

public:
  std::shared_ptr<GameField> Field;

  bool WasRunCalled = false;
};

class Game_IO_Mock : public Game_IO_I {
public:
  virtual void Write(const std::string& text) override {
    WrittenOutput = text;
  }

  virtual std::string Read() override {
    return ReturnInput;
  }

public:
  std::string ReturnInput;
  std::string WrittenOutput;
};

class TetrisControllerTest : public TetrisController {
public:
  std::shared_ptr<GameField> GetGameField() {
    return game_model_->GetField();
  };
};

TEST(TetrisController, ParseEmptyFail) {
  auto io = std::make_shared<Game_IO_Mock>();
  TetrisController controller;
  controller.SetIOInterface(io);

  io->ReturnInput = "";

  EXPECT_THROW(controller.GameInitFromIO(), parse_error);

}

TEST(TetrisController, ParseUnknownCharacterFail) {
  auto io = std::make_shared<Game_IO_Mock>();

  TetrisController controller;
  controller.SetIOInterface(io);

  io->ReturnInput = "1 1\nu";

  EXPECT_THROW(controller.GameInitFromIO(), parse_error);
}

TEST(TetrisController, ParseNoDimensionsFail) {
  auto io = std::make_shared<Game_IO_Mock>();

  TetrisController controller;
  controller.SetIOInterface(io);

  io->ReturnInput = "x x\n#";

  EXPECT_THROW(controller.GameInitFromIO(), parse_error);
}

TEST(TetrisController, ParseWrongDimensionsFail) {
  auto io = std::make_shared<Game_IO_Mock>();

  TetrisController controller;
  controller.SetIOInterface(io);

  io->ReturnInput = "3 3\n#\n#\n";

  EXPECT_THROW(controller.GameInitFromIO(), parse_error);
}

TEST(TetrisController, ParceCorrectField) {
  auto io = std::make_shared<Game_IO_Mock>();

  TetrisControllerTest controller;
  controller.SetIOInterface(io);

  std::stringstream ss;
  ss << "5 6" << '\n';
  ss << "..p..." << '\n';
  ss << "##p.##" << '\n';
  ss << "##pp##" << '\n';
  ss << "##..##" << '\n';
  ss << "##..##" << '\n';

  io->ReturnInput = ss.str();

  controller.GameInitFromIO();
  auto gf = controller.GetGameField();
  auto expected_field = CreateGameField({
    {E, E, G, E, E, E},
    {L, L, G, E, L, L},
    {L, L, G, G, L, L},
    {L, L, E, E, L, L},
    {L, L, E, E, L, L},
  });

  EXPECT_TRUE(AreFieldsEqual(gf, expected_field));
}


TEST(TetrisController, ControllerRunsGame) {
  auto io = std::make_shared<Game_IO_Mock>();
  auto gm = std::make_shared<GameModel_Mock>();

  TetrisController controller;
  controller.SetIOInterface(io);
  controller.SetGameModel(gm);

  controller.GameSimulate();

  EXPECT_TRUE(gm->WasRunCalled);
}

TEST(TetrisController, ControllerCorrectOutputGame) {
  auto io = std::make_shared<Game_IO_Mock>();
  auto gm = std::make_shared<GameModel_Mock>();

  TetrisController controller;
  controller.SetIOInterface(io);
  controller.SetGameModel(gm);

  gm->Field = CreateGameField({
    {E, E, E, G, G, G, E, E, E},
    {E, E, E, G, G, G, E, E, E},
    {E, E, E, G, G, G, E, E, E},
    {E, E, E, L, L, L, E, E, E},
    {E, E, E, L, L, L, E, E, E},
    {E, E, E, L, L, L, E, E, E},
    {L, L, L, L, L, L, L, L, L},
    {L, L, L, L, L, L, L, L, L},
    {L, L, L, L, L, L, L, L, L},
  });
  controller.GamePrint();

  std::stringstream ss;
  ss << "...ppp..." << '\n';
  ss << "...ppp..." << '\n';
  ss << "...ppp..." << '\n';
  ss << "...###..." << '\n';
  ss << "...###..." << '\n';
  ss << "...###..." << '\n';
  ss << "#########" << '\n';
  ss << "#########" << '\n';
  ss << "#########" << '\n';

  EXPECT_EQ(io->WrittenOutput, ss.str());
}