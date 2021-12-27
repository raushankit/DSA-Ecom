#ifndef __SEARCH__
#define __SEARCH__

#include <iostream>
#include <vector>
#include "grp.h"
using namespace std;

struct trie{
    string id;
    unsigned int cat;
    struct trie *child[26];
};

class searchList{
    trie *root;

    trie* getnode();
    void traverse(struct trie*, vector<grp<unsigned int, string>>&);
    public:
    searchList();
    void insert(string,unsigned int,string);
    vector<grp<unsigned int, string>> getList(string);
};

#endif
