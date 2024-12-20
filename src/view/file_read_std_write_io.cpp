//
// Created by notnuff on 19.12.24.
//

#include "file_read_std_write_io.h"

tetris_view::FileReadStdWriteIO::FileReadStdWriteIO(const std::string& tar_dir,
    const std::string& in_file)
      : FileSystemIO_Read(tar_dir, in_file), FileSystemDirectoryIO_I(tar_dir) {


}

std::string tetris_view::FileReadStdWriteIO::Read() {
  return FileSystemIO_Read::Read();
}

void tetris_view::FileReadStdWriteIO::Write(const std::string& text) {
  StdIoWrite::Write(text);
}