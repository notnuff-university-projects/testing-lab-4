#ifndef FILE_SYSTEM_DIRECTORY_BASE_H
#define FILE_SYSTEM_DIRECTORY_BASE_H

#include <string>
#include "game_io_interface.h"

namespace tetris_view {

class FileSystemDirectoryIO_I : public virtual Game_IO_I {
public:
  explicit FileSystemDirectoryIO_I(const std::string& tar_dir);
  virtual ~FileSystemDirectoryIO_I() override = default;

public:
  std::string TargetDirectory();
  void TargetDirectory(const std::string& new_target_dir);

protected:
  std::string target_directory_;

};

}


#endif //FILE_SYSTEM_DIRECTORY_BASE_H
