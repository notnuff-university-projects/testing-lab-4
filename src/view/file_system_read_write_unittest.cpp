#include "file_system_io_write.h"

#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>

#include "file_system_read_write_io.h"

namespace tetris_view {

// helper function to create a file
void CreateFile(const std::string& path, const std::string& content) {
  std::ofstream ofs(path);
  if (!ofs) {
    throw std::runtime_error("Failed to create file: " + path);
  }
  ofs << content;
  ofs.close();
}


TEST(FileSystemReadWriteIO, ReadExisting) {
  std::filesystem::create_directories("./test");
  CreateFile("./test/test-input.txt", "test-input-written");

  FileSystemReadWriteIO fs;
  fs.TargetDirectory("./test");
  fs.TargetInputFile("test-input.txt");

  EXPECT_EQ(fs.Read(), "test-input-written");

  std::filesystem::remove("./test/test-input.txt");
  std::filesystem::remove_all("./test");
}

TEST(FileSystemReadWriteIO, ReadNonExisting) {
  FileSystemReadWriteIO fs;
  fs.TargetDirectory("./nonexistent-directory");
  fs.TargetInputFile("nonexistent.txt");

  // scary structure: test that exception is thrown and has certain message
  EXPECT_THROW({
      try {
          fs.Read();
      } catch( const std::runtime_error& e ) {
          // and this tests that it has the correct message
          EXPECT_STREQ( "Non-existing file", e.what() );
          throw;
      }
  }, std::runtime_error );

}

TEST(FileSystemReadWriteIO, OverwriteExisting) {
  std::filesystem::create_directories("./test");
  CreateFile("./test/test-output.txt", "test-output");

  FileSystemReadWriteIO fs;
  fs.TargetDirectory("./test");
  fs.TargetOutputFile("test-output.txt");
  fs.TargetInputFile("test-output.txt");

  fs.Write("test-output-rewritten");
  EXPECT_EQ(fs.Read(), "test-output-rewritten");

  std::filesystem::remove("./test/test-output.txt");
  std::filesystem::remove_all("./test");
}

TEST(FileSystemReadWriteIO, WriteFailNonExistingDirectory) {
  FileSystemReadWriteIO fs;
  fs.TargetDirectory("./nonexistent-directory");
  fs.TargetOutputFile("test-output.txt");

  EXPECT_THROW({
      try {
          fs.Write("test-output-rewritten");
      } catch( const std::runtime_error& e ) {
          // and this tests that it has the correct message
          EXPECT_STREQ( "Non-existing directory", e.what() );
          throw;
      }
  }, std::runtime_error );
}

// should just create new file
TEST(FileSystemReadWriteIO, WriteNewNonExistingFile) {
  std::filesystem::create_directories("./test");
  EXPECT_FALSE( std::filesystem::exists("./test-output.txt") );

  FileSystemReadWriteIO fs;
  fs.TargetDirectory("./test");
  fs.TargetOutputFile("test-output.txt");
  fs.TargetInputFile("test-output.txt");

  fs.Write("test-output");

  EXPECT_TRUE( std::filesystem::exists("./test/test-output.txt") );
  EXPECT_EQ(fs.Read(), "test-output");

  std::filesystem::remove("./test/test-output.txt");
  std::filesystem::remove_all("./test");
}
}