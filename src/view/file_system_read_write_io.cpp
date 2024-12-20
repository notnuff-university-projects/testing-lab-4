#include "file_system_read_write_io.h"

namespace tetris_view {

FileSystemReadWriteIO::FileSystemReadWriteIO(
    const std::string& tar_dir, const std::string& in_file,
    const std::string& out_file) : FileSystemDirectoryIO_I(tar_dir) {

  TargetInputFile(in_file);
  TargetOutputFile(out_file);
}

}