#include "Page.h"

    void Page::Write(std::ofstream &file){
        this->m_current=file.tellp();
        file.write((char*)this,sizeof(*this));
        file<<std::endl;
    } 
    void Page::Read(std::ifstream &file){
        file.read((char*)this,sizeof(*this));
    }
    void Page::insert(int pos,Record data){
        m_Reg[pos]=data;
    }
    void Page::setSize(int size){
        m_size=size;
    };
