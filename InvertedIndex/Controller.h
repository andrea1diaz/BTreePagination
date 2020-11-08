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
		std::cout<<"start"<<'\n';
		std::ifstream file(filename);
		std::string key,value;
		int cont=0;
		while (!file.eof()){
			std::cout<<cont<<"\n";
			cont++;
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
		std::cout<<"finished"<<std::endl;

		this->files++;
		std::cout<<filelist.size();
		filelist.push_back(filename);
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

	void recover(std::string word,int archivo ) {
        std::shared_ptr<PageManager> pm = std::make_shared<PageManager>("index.dat");
        BTree<Record, BTREE_ORDER> bt(pm);
        //bt.print_tree();
		//bt.print_tree();
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
					file>>logger;
					std::cout<<logger<<", ";					
				}
			}
			std::cout<<"\n";
		}

		
    }

	Controller(){
        bool trunc_file = false;
        auto pm = std::make_shared<PageManager>("index.dat", trunc_file);
        bt = new BTree<Record, BTREE_ORDER>(pm);
	}

private:
    BTree<Record, BTREE_ORDER>* bt;

	std::unordered_map<std::string, node[6]> Dictionary;
	std::vector<std::string> filelist;
	int files=0;
};


