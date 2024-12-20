#ifndef FILESYSTEMIO_WRITE_H
#define FILESYSTEMIO_WRITE_H

#include <string>

#include "file_system_directory_io.h"
#include "game_io_interface.h"

namespace tetris_view {

class FileSystemIO_Write : public virtual FileSystemDirectoryIO_I {
public:
  // creates filesystem io object with default targets
  // target_directory - rsc
  // target_output_file - test-output.txt
  explicit FileSystemIO_Write(const std::string& tar_dir = "",
              const std::string& out_file = "");

  virtual ~FileSystemIO_Write() = default;

  virtual void Write(const std::string& text) override;

  std::string TargetOutputFile();
  void TargetOutputFile(const std::string& new_output_file);

protected:
  std::string target_output_file_;
};

}



#endif //FILESYSTEMIO_WRITE_H
