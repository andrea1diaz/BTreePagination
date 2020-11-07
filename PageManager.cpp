
#include "PageManager.h"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>


PageManager::PageManager(std::string fileName, bool trunc)
    : std::fstream(fileName.data(),
                   std::ios::in | std::ios::out | std::ios::binary) {
  empty = false;
  fileName = fileName;
  if (!good() || trunc) {
    empty = true;
    open(fileName.data(),
         std::ios::in | std::ios::out | std::ios::trunc | std::ios::binary);
  }
}

PageManager::~PageManager() { close(); }