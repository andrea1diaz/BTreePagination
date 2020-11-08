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

	void recover(std::string language_file) {
        /*PageManager record_manager("index.dat");
	    std::shared_ptr<PageManager> pm = std::make_shared<PageManager>("BTree.index");
        BTree<Record, BTREE_ORDER> bt(pm);
        //bt.print_tree();
		//bt.print_tree();
		Record to_find;
		strcpy(to_find.key,"aardvark");
		auto beg = bt.find(to_find);
*/
        PageManager record_manager("index.dat");
        std::shared_ptr<PageManager> pm = std::make_shared<PageManager>("BTree.index");
        BTree<Record, BTREE_ORDER> bt(pm);

        BTree<Record, BTREE_ORDER>::iterator iter = bt.find(r);

        auto record = *iter;
        Record to_find;
        record_manager.recover(record.id, to_find);
        std::cout << record.id << to_find.key << std::endl;
		int a = 0;
    }

	Controller(){
        bool trunc_file = true;
        auto pm = std::make_shared<PageManager>("BTree.index", trunc_file);
        bt = new BTree<Record, BTREE_ORDER>(pm);
	}

private:
    BTree<Record, BTREE_ORDER>* bt;

	std::unordered_map<std::string, node[6]> Dictionary;
	std::vector<std::string> filelist;
	int files=0;
};


