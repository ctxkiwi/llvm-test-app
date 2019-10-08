
#include <string>
#include <fstream>

#include "functions.h"

bool fileExists (const std::string& name) {
  if (FILE *file = fopen(name.c_str(), "r")) {
    fclose(file);
    return true;
  }
  return false;
}

std::string fileGetContents(const std::string &name) {
  std::ifstream ifs(name.c_str());
  std::string content( (std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()) );
  return content;
}
