
#include <iostream>
#include <cstring>

#include "globals.h"

char* text() {
  std::string str = mainModule->getName();
  char* c = strcpy(new char[str.length() + 1], str.c_str());
  return c;
}
