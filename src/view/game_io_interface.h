#ifndef FILE_SYSTEM_IO_INTERFACE_H
#define FILE_SYSTEM_IO_INTERFACE_H
#include <string>

namespace tetris_view {

class Game_IO_I {
public:
  Game_IO_I() = default;
  virtual ~Game_IO_I() = default;

public:
  // making those virtual,
  // so we could implement dependency injection in our tests
  virtual void Write(const std::string& text)=0;
  virtual std::string Read()=0;
};

}

#endif //FILE_SYSTEM_IO_INTERFACE_H
