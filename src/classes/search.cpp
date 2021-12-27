#include "search.h"

searchList::searchList(){
    root = getnode();
}

trie* searchList::getnode(){
    struct trie *p = new trie;
    p->id = "";
    p->cat = 0;
    for(int i = 0;i < 26;i++){
        p->child[i] = NULL;
    }
    return p;
}

void searchList::insert(string prodID, unsigned int categ, string word){
    struct trie *temp = root;
    for(char c : word){
        if((int)c ==32) continue;
        if(c >= 'A' && c <= 'Z') c = ((char)c-'A'+'a');
        if(c==' ') c = ((char)c-'A'+'a');
        if(!temp->child[c-'a']){
            temp->child[c-'a'] = getnode();
        }
        temp = temp->child[c-'a'];
    }
    temp->id = prodID;
    temp->cat = categ;
}

void searchList::traverse(struct trie *node, vector<grp<unsigned int, string>> &v){
    if(node->cat !=0){
        v.push_back(grp<unsigned int,string>(node->cat,node->id));
    }
    for(int i = 0;i < 26;i++){
        if(node->child[i]!=NULL){
            traverse(node->child[i],v);
        }
    }
}

vector<grp<unsigned int, string>> searchList::getList(string word){
    vector<grp<unsigned int, string>> arr;
    arr.clear();
    struct trie *temp = root;
    unsigned int i;
    for(i = 0;i < word.length();i++){
        if(word[i]==' ') continue;
        char c = word[i];
        if(c >= 'A'&& c <= 'Z'){
            c = (char)(c-'A'+'a');
        }
        if(temp->child[c-'a']!=NULL) temp = temp->child[c-'a'];
        else break;
    }
    if(temp==root) return arr;
    traverse(temp,arr);
    return arr;
}

