#pragma once

#include <fstream>
#include <sstream>

std::string load_file(const char* path) {
  char fPath[512];
  full_path(fPath, path);

  std::ifstream stream(fPath, std::ios::in);

  if(!stream.is_open()) {
    printf("ERROR");
    return "ERROR";
  }

  std::stringstream sstream;
  sstream << stream.rdbuf();
  stream.close();

  return sstream.str();
}
