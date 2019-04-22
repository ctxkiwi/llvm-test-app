
#ifndef PACKAGE_C_H
#define PACKAGE_C_H
#endif

#include <map>
#include <vector>
#include <set>

class PackageCompiler {

 public:

  // Functions
  static PackageCompiler* create(std::string rootDir);
  void compileFile(std::string file);
  void loadFile(std::string file);

 private:

 // Vars
  std::map<std::string, PackageCompiler> subPkgCompilers;
  std::string directory;
  Lexer* lexer;
  std::vector<std::string> compileFiles;
  std::set<std::string> compiledFiles;

};
