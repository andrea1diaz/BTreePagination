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

#define BTREE_ORDER 3
#define PAGE_SIZE  64
//#define BTREE_ORDER   ((PAGE_SIZE - (2 * sizeof(long) + sizeof(int) +  2 * sizeof(long)) ) /  (sizeof(int) + sizeof(long)))

Record r;

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
			char key_char[40];
			strcpy(key_char,key.c_str()); 
			if (this->Dictionary.find(key_char)==this->Dictionary.end()){
				this->Dictionary[key_char];				
				this->Dictionary[key_char][files]=temp;

			}else{
				this->Dictionary[key_char][files].insert(address);
			}
		}

		this->files++;
		filelist.push_back(filename);
	}
	
	void write(){
        PageManager record_manager ("index.dat");
        long id = 0;
        for (auto it:Dictionary){
            char key[25];
            strcpy(key,it.first.c_str());
            node value[6];
            for( int i=0;i<6;i++){
                value[i]=it.second[i];
            }
            record_manager.save(id, value);
            bt->insert(Record(key, value, id));
            id++;
            if (id == 1) {
                r = Record(key, value, id - 1);
            }
        }
	}

void recover(std::string word,int archivo ) {
        std::shared_ptr<PageManager> pm = std::make_shared<PageManager>("index.dat");
        BTree<Record, BTREE_ORDER> bt(pm);
		Record to_find;
		strcpy(to_find.key,word.c_str());
		auto beg =bt.find(to_find);
		to_find = (*beg);
		if (strcmp(to_find.key,word.c_str())==0){
			std::fstream file(filelist[archivo]);
			std::string logger;
			for (int i=0;i<10;i++){
				if(to_find.values[archivo].definitions[i]!=-1){
					file.seekg(to_find.values[archivo].definitions[i],std::ios::beg);
					getline(file, logger);
					std::cout<<logger<<", ";					
				}
			}

			std::cout <<'\n';
		}
		
    }

	Controller(){
        bool trunc_file = true;
        auto pm = std::make_shared<PageManager>("BTree.index", trunc_file);
        bt = new BTree<Record, BTREE_ORDER>(pm);
        std::cout << "BTREE ORDER: " << BTREE_ORDER << std::endl;
	}

private:
    BTree<Record, BTREE_ORDER>* bt;

	std::unordered_map<std::string, node[6]> Dictionary;
	std::vector<std::string> filelist;
	int files=0;
};


