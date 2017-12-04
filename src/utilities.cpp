#include "utilities.hpp"
#include <string>
#include <vector>

bool Utilities::FileExists(std::string path) {
  if (FILE *file = fopen(path.c_str(), "r")) {
    fclose(file);
    return true;
  } else {
    return false;
  }
}

std::vector<std::string> Utilities::SplitString(std::string str,
                                                char delimiter) {
  size_t token_counter = 0;
  size_t token_length = 0;

  std::vector<std::string> tokens;
  for (size_t i = 0; i < str.length(); i++) {
    if (str.at(i) != delimiter) {
      if (token_length == 0) {
        tokens.push_back(std::string());
        tokens.at(token_counter).append(&str.at(i), 1);
      } else {
        tokens.at(token_counter).append(&str.at(i), 1);
      }
      token_length++;
    } else {
      token_length = 0;
      token_counter++;
    }
  }

  return tokens;
}
