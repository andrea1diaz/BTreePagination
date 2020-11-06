#pragma once

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

class PageManager : protected std::fstream {

    std::string fileName;
    bool empty;


public:
    PageManager(std::string fileName, bool trunc = false);
    ~PageManager();

    inline bool isEmpty() { return empty; }

    template <class Record> void save(const long &n, Record &rec) {
    clear();
    seekp(n * sizeof(Record), std::ios::beg);
    write(reinterpret_cast<const char *>(&rec), sizeof(rec));
    }

    template <class Register> bool recover(const long &n, Register &rec) {
    clear();
    seekg(n * sizeof(Register), std::ios::beg);
    read(reinterpret_cast<char *>(&rec), sizeof(rec));
    return gcount() > 0;
    }

};