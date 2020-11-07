cmake_minimum_required(VERSION 3.17)
project(BTreePagination)

set(CMAKE_CXX_STANDARD 17)

add_executable(BTreePagination btree_test.cpp BTree.h DataBase.h Page.h PageManager.cpp PageManager.h
        InvertedIndex/Controller.h InvertedIndex/node.h InvertedIndex/node.cpp InvertedIndex/record.h)


