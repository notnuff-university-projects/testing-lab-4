#include "file_system_directory_io.h"

namespace tetris_view {

FileSystemDirectoryIO_I::FileSystemDirectoryIO_I(const std::string& tar_dir)
  : target_directory_(tar_dir) {}

std::string FileSystemDirectoryIO_I::TargetDirectory() {
  return target_directory_;
}

void FileSystemDirectoryIO_I::TargetDirectory(const std::string &new_target_dir) {
  target_directory_ = new_target_dir;
}

}