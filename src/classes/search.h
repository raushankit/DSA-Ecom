#ifndef __SEARCH__
#define __SEARCH__

#include <iostream>
#include <vector>
#include "grp.h"

struct trie
{
    std::string id;
    unsigned int cat;
    struct trie *child[26];
};

class searchList
{
public:
    searchList();
    void insert(std::string, unsigned int, std::string);
    std::vector<grp<unsigned int, std::string>> getList(std::string);

private:
    trie *root;

    trie *getnode();
    void traverse(struct trie *, std::vector<grp<unsigned int, std::string>> &);
};

#endif
