#ifndef UTILITIES_HPP_
#define UTILITIES_HPP_

#include <iostream>
#include <string>
#include <vector>

class Utilities {
 public:
  static bool FileExists(std::string path);
  static std::vector<std::string> SplitString(std::string str, char delimiter);

 private:
  Utilities();
};
#endif  // UTILITIES_HPP_
