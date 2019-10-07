
#include <iostream>
#include <cstring>

char* text() {
  std::string str = "Hello 123";
  char* c = strcpy(new char[str.length() + 1], str.c_str());
  return c;
}
