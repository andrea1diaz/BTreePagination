#include "BTree.h"
#include "PageManager.h"
#include "InvertedIndex/Controller.h"

#include <iostream>
#include <sstream>
#include <algorithm>

// PAGE_SIZE 64 bytes
#define PAGE_SIZE  64 

// Other examples:
// PAGE_SIZE 1024 bytes => 1Kb
// PAGE_SIZE 1024*1024 bytes => 1Mb

// PAGE_SIZE = 2 * sizeof(long) +  (BTREE_ORDER + 1) * sizeof(int) + (BTREE_ORDER + 2) * sizeof(long)  
// PAGE_SIZE = 2 * sizeof(long) +  (BTREE_ORDER) * sizeof(int) + sizeof(int) + (BTREE_ORDER) * sizeof(long) + 2 * sizeof(long)
// PAGE_SIZE = (BTREE_ORDER) * (sizeof(int) + sizeof(long))  + 2 * sizeof(long) + sizeof(int) +  2 * sizeof(long)
//  BTREE_ORDER = PAGE_SIZE - (2 * sizeof(long) + sizeof(int) +  2 * sizeof(long)) /  (sizeof(int) + sizeof(long))
//#define BTREE_ORDER   ((PAGE_SIZE - (2 * sizeof(long) + sizeof(int) +  2 * sizeof(long)) ) /  (sizeof(int) + sizeof(long)))
#define BTREE_ORDER 4

int main () {
  /*bool trunc_file = true;
  std::shared_ptr<PageManager> pm = std::make_shared<PageManager>("BTree.index", trunc_file);
  std::cout << "PAGE_SIZE: " << PAGE_SIZE << std::endl;
  std::cout << "BTREE_ORDER: " << BTREE_ORDER << std::endl;
  BTree<char, BTREE_ORDER> bt(pm);
  std::string values = "qwertyuioplkjhgfdsazxcvbnm";
  for(auto c : values) {
    bt.insert(c);
    bt.print_tree();
  }
  std::ostringstream out;
  bt.print(out);
  std::sort(values.begin(), values.end());*/
  Controller c;
  c.execute("data/French.txt");
  c.write();
  c.recover(".");
  int a = 0;
}
