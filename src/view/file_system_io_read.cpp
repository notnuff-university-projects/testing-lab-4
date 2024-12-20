#include "file_system_io_read.h"

#include <filesystem>
#include <fstream>

namespace tetris_view {

FileSystemIO_Read::FileSystemIO_Read(
  const std::string& tar_dir,
  const std::string& in_file) : FileSystemDirectoryIO_I(tar_dir) {

  TargetInputFile(in_file);
}


std::string FileSystemIO_Read::Read() {
  std::string separator = target_directory_.ends_with("/") ? "" : "/";
  std::string full_path = target_directory_ + separator + target_input_file_;

  if( !std::filesystem::exists(full_path) ) {
    throw std::runtime_error("Non-existing file");
  }

  std::ifstream input_file(full_path);
  if (!input_file.is_open()) {
    throw std::runtime_error("Unable to open file for reading");
  }

  std::ostringstream buffer;
  buffer << input_file.rdbuf();

  input_file.close();

  return buffer.str();
}



std::string FileSystemIO_Read::TargetInputFile() {
  return target_input_file_;
}

void FileSystemIO_Read::TargetInputFile(const std::string &new_input_file) {
  target_input_file_ = new_input_file;
}

}