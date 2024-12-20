#ifndef FILESYSTEMIO_H
#define FILESYSTEMIO_H

#include "file_system_io_read.h"
#include "file_system_io_write.h"

namespace tetris_view {

class FileSystemReadWriteIO :
  public virtual FileSystemIO_Read,
  public virtual FileSystemIO_Write {

public:
  explicit FileSystemReadWriteIO(const std::string& tar_dir = "",
                const std::string& in_file = "",
                const std::string& out_file = ""
                );
};

}


#endif //FILESYSTEMIO_H
