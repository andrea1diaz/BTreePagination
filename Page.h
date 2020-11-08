#pragma once

template <class T, int BTREE_ORDER = 3> class Page {
    long Page_id{-1};
    long count{0};

    T data[BTREE_ORDER + 1];
    long children[BTREE_ORDER + 2];

    Page(long Page_id) : Page_id{Page_id} {
        count = 0;
        for (int i = 0; i < BTREE_ORDER + 2; i++) {
            children[i] = 0;
        }
    }

    void insert_in_Page(int pos, const T &value) {
        int j = count;
        while (j > pos) {
            data[j] = data[j - 1];
            children[j + 1] = children[j];
            j--;
        }
        data[j] = value;
        children[j + 1] = children[j];
        count++;
    }

    bool is_overflow() { return count > BTREE_ORDER; }
};
