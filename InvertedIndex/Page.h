#include <bits/stdc++.h>
#include "record.h"

class Page { 
private: 
    Record m_Reg[20];
    int m_size; 
    int m_current;
    unsigned long m_pNext; 
public: 
    Page(){};
    void setSize(int size); 
    void Write(std::ofstream &file); 
    void Read(std::ifstream &file); 
    void insert(int pos,Record data);
}; 