#include "inverted_index.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

//inverted_index::inverted_index () {}

/*void inverted_index::add(std::string filename, std::string word) {
	std::transform(word.begin(), word.end(), word.begin(), tolower);
	
	filelist.push_back(filename);

	node new_node(filename);

	Dictionary[word].push_back(new_node);
}

void inverted_index::add(std::string filename, std::vector<std::string> word_vector) {
	for (auto i : word_vector) {
		add(filename, i);
	}
}


void inverted_index::find(std::string word) {
	if (Dictionary.find(word) != Dictionary.end()) {
		int len = (int)Dictionary[word].size();

		for (int i = 0; i < len; ++i) {
			std::cout << Dictionary[word][i].filename << '\n';
		}
	}

	else std::cout << "word not found\n";
}



bool sortby(const std::pair<std::string, std::vector<node>> &a, 
              const std::pair<std::string, std::vector<node>> &b) { 
    return (a.first < b.first); 
}


void inverted_index::save_to(std::string filename) {
	std::vector<std::pair<std::string, std::vector<node>>> tmp(Dictionary.begin(), Dictionary.end());
	
	std::sort(tmp.begin(), tmp.end(), sortby);

	std::fstream file(filename, std::ios::out);
	
	for (int i = 0; i < tmp.size(); ++i) {
		file << tmp[i].first << ": ";
	
		int len = (int)tmp[i].second.size();

		for (int j = 0; j < len; ++j) {
			file << tmp[i].second[j].filename << " ";
		}

		file << '\n';
	}

	file.close();
}

void inverted_index::execute(std::string filename){
	std::ifstream file(filename);
	std::string key,value;
	while (!file.eof()){
		
		getline(file,key,'\t');
		int address=file.tellg();
		node temp;
		temp.insert(address);
		getline(file,value);
		if (this->Dictionary.find(key)==this->Dictionary.end()){
			this->Dictionary[key];
			this->Dictionary[key][files]=temp;

		}else{
			this->Dictionary[key][files].insert(address);
		}
	}

	this->files++;


}*/