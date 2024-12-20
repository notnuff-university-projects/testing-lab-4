#ifndef STD_IO_WRITE_H
#define STD_IO_WRITE_H
#include "game_io_interface.h"


namespace tetris_view {

class StdIoWrite : public virtual Game_IO_I {
public:
  StdIoWrite() = default;
  virtual ~StdIoWrite() override = default;

public:
  virtual void Write(const std::string& text) override;

};

}

#endif //STD_IO_WRITE_H
