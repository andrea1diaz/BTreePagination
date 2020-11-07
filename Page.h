#pragma once

template <class T, int BTREE_ORDER = 3> class Page {
public:
    T keys[BTREE_ORDER + 1];
    long children[BTREE_ORDER + 2];
    long data[BTREE_ORDER + 2];

    long pageId{-1};
    long next_id{-1};
    long nKeys{0};
    bool isLeaf{true};

    Page(long page_id) : pageId{page_id} {
        nKeys = 0;
        for (int i = 0; i < BTREE_ORDER + 2; i++) { //init with zeros
            children[i] = 0;
        }
    }
    Page(long page_id, bool is_leaf) : pageId{page_id}, isLeaf{is_leaf} {
        nKeys = 0;
        for (int i = 0; i < BTREE_ORDER + 2; i++) { //init with zeros
            children[i] = 0;
        }
    }

    void insertInPage(int pos, const T &value, const long dataId) {
        int j = nKeys;
        while (j > pos) {
            keys[j] = keys[j - 1];
            data[j] = data[j - 1];
            children[j + 1] = children[j];
            j--;
        }
        keys[j] = value;
        data[j] = dataId;
        children[j + 1] = children[j];
        nKeys++;
    }

    bool isOverflow() { return nKeys > BTREE_ORDER; }

};