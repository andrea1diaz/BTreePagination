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
		long cont = 0;
		for (auto it:Dictionary){
			char key[25];
			strcpy(key,it.first.c_str());
			node value[6];
			for( int i=0;i<6;i++){
				value[i]=it.second[i];
			}
			bt->insert(Record(cont,key,value));
			cont++;
		}
	}

	void recover(std::string language_file) {
        PageManager record_manager ("index.dat");

        std::shared_ptr<PageManager> pm = std::make_shared<PageManager>("BTree.index");
        BTree<Record, BTREE_ORDER> bt(pm);
        BTree<Record, BTREE_ORDER>::iterator iter = bt.begin();
        BTree<Record, BTREE_ORDER>::iterator end = bt.end();
        for (; iter != end; iter++) {
            auto record = *iter;
            Record r;
            record_manager.recover(record.id, r);
            std::cout << record.id << " " << record.key << " ";
            for (auto& node: record.values) {
                for (auto& pos : node.definitions) {
                    std::cout << pos << " ";
                }
                std::cout << "||";
            }
            std::cout << "\n";
        }

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


