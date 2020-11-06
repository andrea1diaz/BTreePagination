#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "inverted_index.cpp"

int main () {
	inverted_index index;

	index.execute("data/French.txt");
	index.write();



}
