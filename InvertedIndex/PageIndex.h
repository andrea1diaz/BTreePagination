#include <iostream>
#include <fstream>

#include "record.h"

    class PageIndex {
    private:
        Record m_Reg[20];
        int m_size;
        int m_current;
        unsigned long m_pNext;
    public:
        PageIndex() {};

        void setSize(int size);

        void Write(std::ofstream &file);

        void Read(std::ifstream &file);

        void insert(int pos, Record data);
    };