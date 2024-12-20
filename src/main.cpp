#include "model/tetris.h"

#include <matrices/matrix.h>

#include "controller/tetris_controller.h"
#include "view/file_read_std_write_io.h"
#include "view/std_io_write.h"

using namespace tetris_controller;
using namespace tetris_model;
using namespace tetris_view;

int main() {
  auto io_component =
    std::make_shared<FileReadStdWriteIO>("rsc", "test-input.txt");
  auto controller =
    std::make_shared<TetrisController>();
  controller->SetIOInterface(io_component);

  controller->GameInitFromIO();
  controller->GameSimulate();
  controller->GamePrint();
}