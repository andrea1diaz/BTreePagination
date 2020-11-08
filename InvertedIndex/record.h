#include <cstring>
#include "node.h"


class Record{
public:
    long id;
    char key[25];
    node values[6];
    Record( char _key[25],node _values[6], long _id){
        for(int i=0;i<25;i++ ){
            key[i]=_key[i];
        }
        for(int i=0;i<6;i++ ){
            values[i]=_values[i];
        }

        id = _id;

    }
    Record(){
        strncpy(key,"",25);
    }
    bool operator<(const Record &other){
        std::string s = this->key;
        std::string o = other.key;
        return (s.compare(o) > 0);
    }

    bool operator>(const Record &other){
        std::string s = this->key;
        std::string o = other.key;
        return (s.compare(o) < 0);
    }

    bool operator==(const Record &other) const{
        std::string s = this->key;
        std::string o = other.key;
        return s == o;
    }

    Record& operator=(const Record& other ){
        for(int i=0;i<25;i++ ){
            key[i]=other.key[i];
        }
        for(int i=0;i<6;i++ ){
            values[i]=other.values[i];
        }
        return *this;
    }

    void print(){
        std::cout<<key<<" ";
        for(int i=0;i<6;i++){
            for(int j=0;j<10;j++){
                std::cout<<values[i].definitions[j]<<" ";
            }
            std::cout<<" || ";
        }
    }
};

