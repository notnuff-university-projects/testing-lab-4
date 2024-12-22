#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exceptions/exceptions.h>
#include "tetris_controller.h"
#include "game_field_common.h"

using namespace tetris_controller;
using namespace tetris_model;
using namespace tetris_view;

class MockGameModel : public Game {
public:
    explicit MockGameModel() : Game(CreateGameField({{E}})) {}


    MOCK_METHOD(void, Run, (), (override));
    MOCK_METHOD(void, MakeStep, (), (override));
    MOCK_METHOD(bool, IsCanMakeStep, (), (override));
    MOCK_METHOD(std::shared_ptr<GameField>, GetField, (), (const, override));

};

class MockGameIO : public Game_IO_I {
public:
    MOCK_METHOD(void, Write, (const std::string& text), (override));
    MOCK_METHOD(std::string, Read, (), (override));
};

std::shared_ptr<GameField> CreateExpectedGameField() {
    return CreateGameField({
        {E, E, G, E, E, E},
        {L, L, G, E, L, L},
        {L, L, G, G, L, L},
        {L, L, E, E, L, L},
        {L, L, E, E, L, L},
    });
}

class TetrisControllerTest : public ::testing::Test {
protected:
    std::shared_ptr<MockGameIO> mock_io;
    std::shared_ptr<MockGameModel> mock_game_model;
    TetrisController controller;

    void SetUp() override {
        mock_io = std::make_shared<MockGameIO>();
        mock_game_model = std::make_shared<MockGameModel>();
        controller.SetIOInterface(mock_io);
        controller.SetGameModel(mock_game_model);
    }
};

TEST_F(TetrisControllerTest, ParseEmptyFail) {
    EXPECT_CALL(*mock_io, Read()).WillOnce(::testing::Return(""));

    EXPECT_THROW(controller.GameInitFromIO(), parse_error);
}

TEST_F(TetrisControllerTest, ParseUnknownCharacterFail) {
    EXPECT_CALL(*mock_io, Read()).WillOnce(::testing::Return("1 1\nu"));

    EXPECT_THROW(controller.GameInitFromIO(), parse_error);
}

TEST_F(TetrisControllerTest, ParseNoDimensionsFail) {
    EXPECT_CALL(*mock_io, Read()).WillOnce(::testing::Return("x x\n#"));

    EXPECT_THROW(controller.GameInitFromIO(), parse_error);
}

TEST_F(TetrisControllerTest, ParseWrongDimensionsFail) {
    EXPECT_CALL(*mock_io, Read()).WillOnce(::testing::Return("3 3\n#\n#\n"));

    EXPECT_THROW(controller.GameInitFromIO(), parse_error);
}

TEST_F(TetrisControllerTest, ParseCorrectField) {
    std::stringstream ss;
    ss << "5 6" << '\n';
    ss << "..p..." << '\n';
    ss << "##p.##" << '\n';
    ss << "##pp##" << '\n';
    ss << "##..##" << '\n';
    ss << "##..##" << '\n';

    EXPECT_CALL(*mock_io, Read()).WillOnce(::testing::Return(ss.str()));

    EXPECT_CALL(*mock_game_model, GetField()).WillOnce(::testing::Return(CreateExpectedGameField()));

    controller.GameInitFromIO();

    auto game_field = mock_game_model->GetField();
    auto expected_field = CreateExpectedGameField();

    EXPECT_TRUE(AreFieldsEqual(game_field, expected_field));
}

TEST_F(TetrisControllerTest, ControllerRunsGame) {
    auto expected_field = CreateExpectedGameField();

    EXPECT_CALL(*mock_game_model, GetField()).WillOnce(::testing::Return(expected_field));
    EXPECT_CALL(*mock_game_model, Run()).Times(1);

    controller.GameRun(false);
}

TEST_F(TetrisControllerTest, ControllerCorrectOutputGame) {
    auto field = CreateGameField({
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

    EXPECT_CALL(*mock_game_model, GetField()).WillOnce(::testing::Return(field));

    std::stringstream expected_output;
    expected_output << "...ppp..." << '\n';
    expected_output << "...ppp..." << '\n';
    expected_output << "...ppp..." << '\n';
    expected_output << "...###..." << '\n';
    expected_output << "...###..." << '\n';
    expected_output << "...###..." << '\n';
    expected_output << "#########" << '\n';
    expected_output << "#########" << '\n';
    expected_output << "#########" << '\n';
    expected_output << '\n';

    EXPECT_CALL(*mock_io, Write(expected_output.str())).Times(1);

    controller.GameRun(false);
}

TEST_F(TetrisControllerTest, ControllerRunsGameStepByStep) {
  auto step_0_field = CreateGameField({
      {E, E, G, E, E, E, E, E},
      {E, E, G, G, G, E, E, E},
      {E, E, G, E, E, E, E, E},
      {E, E, E, E, E, E, E, E},
      {E, E, E, L, E, E, E, E},
      {E, E, E, L, E, E, L, E},
      {L, L, L, L, L, L, L, E},
  });

  auto step_1_field = CreateGameField({
        {E, E, E, E, E, E, E, E},
        {E, E, G, E, E, E, E, E},
        {E, E, G, G, G, E, E, E},
        {E, E, G, E, E, E, E, E},
        {E, E, E, L, E, E, E, E},
        {E, E, E, L, E, E, L, E},
        {L, L, L, L, L, L, L, E},
  });

  auto step_2_field = CreateGameField({
        {E, E, E, E, E, E, E, E},
        {E, E, E, E, E, E, E, E},
        {E, E, G, E, E, E, E, E},
        {E, E, G, G, G, E, E, E},
        {E, E, G, L, E, E, E, E},
        {E, E, E, L, E, E, L, E},
        {L, L, L, L, L, L, L, E},
  });

  EXPECT_CALL(*mock_game_model, IsCanMakeStep())
      .WillOnce(::testing::Return(true))
      .WillOnce(::testing::Return(true))
      .WillOnce(::testing::Return(false));

  EXPECT_CALL(*mock_game_model, MakeStep()).Times(2);

  EXPECT_CALL(*mock_game_model, GetField())
      .WillOnce(::testing::Return(step_0_field))
      .WillOnce(::testing::Return(step_1_field))
      .WillOnce(::testing::Return(step_2_field));

  EXPECT_CALL(*mock_io, Write("STEP 0\n"));

  std::stringstream step_0_output;
  step_0_output << "..p....." << '\n';
  step_0_output << "..ppp..." << '\n';
  step_0_output << "..p....." << '\n';
  step_0_output << "........" << '\n';
  step_0_output << "...#...." << '\n';
  step_0_output << "...#..#." << '\n';
  step_0_output << "#######." << '\n';
  step_0_output << '\n';
  EXPECT_CALL(*mock_io, Write(step_0_output.str()));

  EXPECT_CALL(*mock_io, Write("STEP 1\n"));
  std::stringstream step_1_output;
  step_1_output << "........" << '\n';
  step_1_output << "..p....." << '\n';
  step_1_output << "..ppp..." << '\n';
  step_1_output << "..p....." << '\n';
  step_1_output << "...#...." << '\n';
  step_1_output << "...#..#." << '\n';
  step_1_output << "#######." << '\n';
  step_1_output << '\n';
  EXPECT_CALL(*mock_io, Write(step_1_output.str()));

  EXPECT_CALL(*mock_io, Write("STEP 2\n"));
  std::stringstream step_2_output;
  step_2_output << "........" << '\n';
  step_2_output << "........" << '\n';
  step_2_output << "..p....." << '\n';
  step_2_output << "..ppp..." << '\n';
  step_2_output << "..p#...." << '\n';
  step_2_output << "...#..#." << '\n';
  step_2_output << "#######." << '\n';
  step_2_output << '\n';
  EXPECT_CALL(*mock_io, Write(step_2_output.str()));

  controller.GameRun(true);
}