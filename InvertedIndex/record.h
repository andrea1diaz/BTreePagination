#include "node.h"


class Record{
    public:
    char key[25];
    node values[6];
    Record(char _key[25],node _values[6] ){
        for(int i=0;i<25;i++ ){
            key[i]=_key[i];
        }
        for(int i=0;i<6;i++ ){
            values[i]=_values[i];
        }
        

    }
    Record(){
        strncpy(key,"",25);
    }
    bool operator<(const Record &other){
        for (int i=0;i<25;i++){
            if (this->key[i]>other.key[i]){
                return false;
            }else if(this->key[i]<other.key[i]){
                return true;
            }
        }
        return false;
    }

    bool operator>(const Record &other){
        for (int i=0;i<25;i++){
            if (this->key[i]<other.key[i]){
                return false;
            }else if(this->key[i]>other.key[i]){
                return true;
            }
        }
        return false;
    }

    bool operator==(const Record &other){
        return strcmp(other.key,this->key);
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
};

