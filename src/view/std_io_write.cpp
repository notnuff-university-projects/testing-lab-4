#include "std_io_write.h"

#include <iostream>
#include <ostream>

namespace tetris_view {

void StdIoWrite::Write(const std::string& text) {
  std::cout << text << '\n';
}

}