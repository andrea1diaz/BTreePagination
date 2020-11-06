#include "node.h"

#include <iostream>
#include <string>

void node::insert(int pos){
	this->definitions[size]=pos;
	this->size++;
}