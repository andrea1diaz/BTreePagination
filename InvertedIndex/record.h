#include <cstring>
#include "node.h"
#define key_size 40

class Record{
    public:
    char key[key_size];
    node values[6];
    Record( char _key[key_size],node _values[6] ){
        for(int i=0;i<key_size;i++ ){
            key[i]=_key[i];
        }
        for(int i=0;i<6;i++ ){
            values[i]=_values[i];
        }

    }
    Record(){
        strncpy(key,"",key_size);
    }
    bool operator<(const Record &other){
        for (int i=0;i<key_size;i++){
            if (this->key[i]>other.key[i]){
                return false;
            }else if(this->key[i]<other.key[i]){
                return true;
            }
        }
        return false;
    }

    bool operator>(const Record &other){
        for (int i=0;i<key_size;i++){
            if (this->key[i]<other.key[i]){
                return false;
            }else if(this->key[i]>other.key[i]){
                return true;
            }
        }
        return false;
    }

    bool operator==(const Record &other) const{
        for(int i=0;i<key_size;i++){
            if(key[i]!=other.key[i]){
                return false;
            }
        }
        return true;
    }

    Record& operator=(const Record& other ){
        for(int i=0;i<key_size;i++ ){
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

