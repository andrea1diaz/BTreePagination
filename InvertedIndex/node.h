#pragma once

#include <iostream>

class node {
public:
	node(){
		for(int i=0;i<10;i++){
			definitions[i]=-1;
		}
	};
	int size=0;
	
	int definitions[10];  
	void insert(int pos);
	
};

