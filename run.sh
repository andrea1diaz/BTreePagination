clear
rm a.out
g++ btree_test.cpp BTree.h DataBase.h Page.h PageManager.cpp PageManager.h InvertedIndex/Controller.h InvertedIndex/node.h InvertedIndex/node.cpp InvertedIndex/record.h 
./a.out
find . -name "*.gch" -type f -delete