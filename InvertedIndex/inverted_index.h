#pragma once
#include "node.h"
#include "PageIndex.h"
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <stdio.h>
#include <string.h>

class inverted_index {
public:

	/*void add(std::string filename, std::string word);
	void add(std::string filename, std::vector<std::string> word_vector);
    void find(std::string word);
	void save_to(std::string filename);
	*/
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
		std::ofstream file("index.dat");
		PageIndex page;
		int cont=0;
		for (auto it:Dictionary){
			if(cont==20){ 
				page.setSize(20);
				page.Write(file);
				cont=0;
			}
			char key[25];
			strcpy(key,it.first.c_str());
			node value[6];
			for( int i=0;i<6;i++){
				value[i]=it.second[i];
			}
			
			page.insert(cont,Record(key,value));
			cont++;
		}
		if (cont){
			page.setSize(cont);
			page.Write(file);
		}
	}
	inverted_index()=default;

private:
	PageIndex* root;
	std::unordered_map<std::string, node[6]> Dictionary;
	std::vector<std::string> filelist;
	int files=0;
};


