#include "BTree.h"
#include "InvertedIndex/Controller.h"

int main () {
  Controller c;
  c.execute("data/French.txt");
  c.execute("data/Italian.txt");
  c.execute("data/Portuguese.txt");
  c.execute("data/Spanish.txt");
  c.write();
  for (int i = 0; i < 4; ++i) {
      c.recover("house",i);
  }
}
