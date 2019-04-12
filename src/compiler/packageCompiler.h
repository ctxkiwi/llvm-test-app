
#ifndef PACKAGE_C_H
#define PACKAGE_C_H
#endif

#include <map>

class PackageCompiler {
 public:
  static PackageCompiler* create(std::string rootDir);
 private:
  std::map<std::string, PackageCompiler> subPkgCompilers;
  std::string directory;
  Lexer* lexer;
};
