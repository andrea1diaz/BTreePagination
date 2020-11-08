#pragma once

#include "PageManager.h"
#include "Page.h"
#include <memory>
#include <experimental/optional>



template <class T, int BTREE_ORDER = 3> class BTree {

    struct Header {
    long rootId{1};
    long nPages{0};
    } header;
    
    enum state {
      OVERFLOW,
      UNDERFLOW,
      NORMAL,
    };

    typedef std::shared_ptr<PageManager> pageManager;
    typedef Page<T, BTREE_ORDER> BTreePage;

    pageManager pm;

public:
    
    BTree(pageManager pm) : pm{pm} {
        if (pm->isEmpty()) {
            BTreePage root(header.rootId, true);
            pm->save(root.pageId, root);
            header.nPages++;
            pm->save(0, header);
        } else 
            pm->recover(0, header);
    }

    BTreePage createPage(bool isLeaf) {
        header.nPages++;
        BTreePage newPage(header.nPages, isLeaf);
        pm->save(0, header);
        return newPage;
    }

    BTreePage readPage(long pageId) {
        BTreePage newPage(-1);
        pm->recover(pageId, newPage);
        return newPage;
    }

    bool writePage(long pageId, BTreePage page) {
        pm->save(pageId, page);
        return true;
    }

    void insert(const T &value, const long dataId = -1) {
        BTreePage root = readPage(header.rootId);
        int state = insert(root, value, dataId);
        if (state == OVERFLOW) splitRoot();
    }

    int insert(BTreePage &ptr, const T &value, const long dataId) {
        int pos = 0;
        while (pos < ptr.nKeys && ptr.keys[pos] < value)
            pos++;

        if (ptr.isLeaf) {
            ptr.insertInPage(pos, value, dataId);
            writePage(ptr.pageId, ptr);
        } else {
            long pageId = ptr.children[pos];
            BTreePage child = readPage(pageId);
            int state = insert(child, value, dataId);
            if (state == OVERFLOW) split(ptr, pos);
        }
        return ptr.isOverflow() ? OVERFLOW : NORMAL;
    }

    void split(BTreePage &parent, int pos) {
        BTreePage overflowPage = this->readPage(parent.children[pos]);
        BTreePage newPage = this->createPage(overflowPage.isLeaf);

        int iter = BTREE_ORDER / 2;
        int i;
        overflowPage.nKeys= iter;
        parent.insertInPage(pos, overflowPage.keys[iter], overflowPage.data[iter]);//promotion
        iter++; // the middle element

        for (i = 0; iter < BTREE_ORDER + 1; i++) {
            newPage.children[i] = overflowPage.children[iter];
            newPage.keys[i] = overflowPage.keys[iter];
            newPage.nKeys++;
            iter++;
        }
        newPage.children[i] = overflowPage.children[iter];

        parent.children[pos] = overflowPage.pageId;
        parent.children[pos + 1] = newPage.pageId;

        writePage(parent.pageId, parent);
        writePage(overflowPage.pageId, overflowPage);
        writePage(newPage.pageId, newPage);
    }

    void splitRoot() {
        BTreePage overflowPage = this->readPage(this->header.rootId);
        BTreePage leftPage = this->createPage(overflowPage.isLeaf);
        BTreePage rightPage = this->createPage(overflowPage.isLeaf);

        int pos = 0;
        int iter = 0;
        int i;

        for (i = 0; iter < BTREE_ORDER / 2; i++) {
            leftPage.children[i] = overflowPage.children[iter];
            leftPage.keys[i] = overflowPage.keys[iter];
            leftPage.nKeys++;
            iter++;
        }

        leftPage.children[i] = overflowPage.children[iter];
        iter++; // the middle element

        for (i = 0; iter < BTREE_ORDER + 1; i++) {
            rightPage.children[i] = overflowPage.children[iter];
            rightPage.keys[i] = overflowPage.keys[iter];
            rightPage.nKeys++;
            iter++;
        }
        rightPage.children[i] = overflowPage.children[iter];

        overflowPage.children[pos] = leftPage.pageId;
        overflowPage.keys[0] = overflowPage.keys[BTREE_ORDER / 2];
        overflowPage.children[pos + 1] = rightPage.pageId;
        overflowPage.nKeys = 1;
        overflowPage.isLeaf = false;

        writePage(overflowPage.pageId, overflowPage);
        writePage(leftPage.pageId, leftPage);
        writePage(rightPage.pageId, rightPage);
    }

    void print(std::ostream& out) {
        BTreePage root = readPage(header.rootId);
        print(root, 0, out);
    }

    void print(BTreePage &ptr, int level, std::ostream& out) {
        int i;
        for (i = 0; i < ptr.nKeys; i++) {
          if (ptr.children[i]) {
            BTreePage child = readPage(ptr.children[i]);
            print(child, level + 1, out);
          }
          out << ptr.keys[i];
          std::cout<<std::endl;
        }
        if (ptr.children[i]) {
          BTreePage child = readPage(ptr.children[i]);
          print(child, level + 1, out);
        }
    }
public:
    class iterator : std::iterator< std::forward_iterator_tag,T,T,T*,T& > {
        std::experimental::optional<BTreePage> root;
        std::experimental::optional<BTreePage> ending;
        int pos	= 0;
        int pos_end	= 0;
        BTree<T, BTREE_ORDER>* instance;
    public:
        iterator(BTree* instance) : instance(instance){}
        iterator(BTree* instance, BTreePage start){
            root = std::experimental::make_optional(start);
        }
        
        iterator(BTree* instance, BTreePage start, int count) : instance(instance) {
            root = std::experimental::make_optional(start);
            pos = count;
        }
        iterator(BTree* instance, BTreePage start, int count, BTreePage end, int count_end) : instance(instance){
            root = std::experimental::make_optional(start);
            ending = std::experimental::make_optional(end);
            pos = count;
            pos_end = count_end;
        }
        iterator& operator++(){
            // if root does exists/null
            if (!root) {
                return *this;
            }

            // if pos does not overflow root
            if (root.value().nKeys - 1 > pos) {
                pos ++;
                return *this;
            }

            // if pos++ is at the end BTreePage
            if (ending && ending.value().keys[pos_end] == root.value().keys[pos]) {
                root = std::experimental::nullopt;
                return *this;
            }

            // id pos++ is in the next BTreePage
            root = std::experimental::make_optional(instance->readPage(root.value().children[pos]));
            return *this;
        }
        iterator operator++(int){
            iterator it = *this;
            ++(*this);
            return *this;
        }


        bool operator==(iterator& it) const{
            if (!root && !it.root) return true;

            if (!root || !it.root) return false;

            if (root.value().keys[pos] == it.root.value().keys[pos]) {
                return true;
            }
        }


        bool operator!=(iterator& it) const{
            return !(*this == it);
        }


        T operator*(){
            return root.value().keys[pos];
        }
    };

    iterator end () {
        return iterator(this);
    }

    iterator begin() {
        BTreePage root = readPage (header.rootId);
        return iterator(this, root);
    }

    iterator find (const T &value) {
        BTreePage root = readPage(header.rootId);
        return find(root, 0, value);
    }

    iterator find (BTreePage &ptr, int level, const T &value) {
        int i;

        for (i = 0; i < ptr.nKeys; i++) {
            if (ptr.keys[i] > value) {
                break;
            }
        }   
        if (ptr.isLeaf || ptr.keys[i]==value){     
            return iterator(this,ptr,i);                 
        }else{
            BTreePage child = readPage(ptr.children[i ]);
            return find(child,level+1,value);
        }

    }


  void print_tree() {
    BTreePage root = readPage(header.rootId);
    print_tree(root, 0);
    std::cout << "________________________\n";
  }

  void print_tree(BTreePage &ptr, int level) {
    int i;
    for (i = ptr.nKeys - 1; i >= 0; i--) {
      if (ptr.children[i + 1]) {
        BTreePage child = readPage(ptr.children[i + 1]);
        print_tree(child, level + 1);
      }

      for (int k = 0; k < level; k++) {
        std::cout << "    ";
      }
       ptr.keys[i].print();
    }
    if (ptr.children[i + 1]) {
      BTreePage child = readPage(ptr.children[i + 1]);
      print_tree(child, level + 1);
    }
  }



};