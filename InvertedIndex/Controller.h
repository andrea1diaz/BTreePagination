#pragma once
#include "node.h"
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <cstring>
#include "../BTree.h"
#include "../PageManager.h"
#include "record.h"

#define BTREE_ORDER 4
#define PAGE_SIZE  64

class Controller {
public:

	void execute(std::string filename){
		std::ifstream file(filename);
		std::string key,value;
		while (!file.eof()){
			
			getline(file,key,'\t');
			int address=file.tellg();
			node temp;
			temp.insert(address);
			getline(file,value);
			char key_char[25];
			strcpy(key_char,key.c_str()); 
			std::cout<<"key: "<<key<<" value: "<<value<<"\n";
			if (this->Dictionary.find(key_char)==this->Dictionary.end()){
				this->Dictionary[key_char];				
				this->Dictionary[key_char][files]=temp;

			}else{
				this->Dictionary[key_char][files].insert(address);
			}
		}

		this->files++;
/*for(auto it:Dictionary){
			std::cout<<"key: "<<it.first<< " values: ";
			for(auto it2:it.second){
				for(auto it3:it2.definitions){
					std::cout<<it3<<" ";
				}

			}
			std::cout<<std::endl;
		}*/
	}
	
	void write(){
		for (auto it:Dictionary){
			char key[25];
			strcpy(key,it.first.c_str());
			node value[6];
			for( int i=0;i<6;i++){
				value[i]=it.second[i];
			}
			bt->insert(Record(key,value));
		}
	}

	void recover(std::string language_file) {
        std::shared_ptr<PageManager> pm = std::make_shared<PageManager>("index.dat");
        BTree<Record, BTREE_ORDER> bt(pm);
        bt.print_tree();


    }

	Controller(){
        bool trunc_file = true;
        auto pm = std::make_shared<PageManager>("index.dat", trunc_file);
        bt = new BTree<Record, BTREE_ORDER>(pm);
	}

private:
    BTree<Record, BTREE_ORDER>* bt;

	std::unordered_map<std::string, node[6]> Dictionary;
	std::vector<std::string> filelist;
	int files=0;
};


