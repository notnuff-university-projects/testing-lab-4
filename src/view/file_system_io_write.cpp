#include "file_system_io_write.h"

#include <filesystem>
#include <fstream>
namespace tetris_view {

FileSystemIO_Write::FileSystemIO_Write(
  const std::string& tar_dir,
  const std::string& out_file) : FileSystemDirectoryIO_I(tar_dir) {

  TargetOutputFile(out_file);
}

void FileSystemIO_Write::Write(const std::string& text) {
  std::string separator = target_directory_.ends_with("/") ? "" : "/";
  std::string full_path = target_directory_ + separator + target_output_file_;

  if( !std::filesystem::exists(target_directory_) ) {
    throw std::runtime_error("Non-existing directory");
  }

  std::ofstream output_file(full_path, std::ios::out);

  if (!output_file.is_open()) {
    throw std::runtime_error("Unable to open or create file for writing");
  }

  output_file << text;
  output_file.close();
}

std::string FileSystemIO_Write::TargetOutputFile() {
  return target_output_file_;
}

void FileSystemIO_Write::TargetOutputFile(const std::string &new_output_file) {
  target_output_file_ = new_output_file;
}
}