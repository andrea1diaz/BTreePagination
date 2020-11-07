#include "PageIndex.h"
#include <iostream>

    void PageIndex::Write(std::ofstream &file) {
        this->m_current = file.tellp();
        file.write((char *) this, sizeof(*this));
        file << std::endl;
    }

    void PageIndex::Read(std::ifstream &file) {
        file.read((char *) this, sizeof(*this));
    }

    void PageIndex::insert(int pos, Record data) {
        m_Reg[pos] = data;
    }

    void PageIndex::setSize(int size) {
        m_size = size;
    };
