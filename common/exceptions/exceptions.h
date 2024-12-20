#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>

namespace tetris_model {

class init_error : public std::runtime_error {
public:
  explicit init_error(const std::string& msg) : std::runtime_error(msg){}
};

class parse_error : public std::runtime_error {
public:
  explicit parse_error(const std::string& msg) : std::runtime_error(msg){}
};

}



#endif //EXCEPTIONS_H
