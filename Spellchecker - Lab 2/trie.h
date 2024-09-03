#include <iostream>
#include <string>
#ifndef TRIE_H
#define TRIE_H

    class trienode{
        public:
       trienode *children[26];
        bool isendofword;   
        // constructor to initlize array of size 26 for each letter to null since nothings in it, end of word is false bc again, nothing is in it
        trienode() {
            for (int i = 0; i < 26; ++i) {
                children[i] = nullptr;
            }
            isendofword = false;
        }
        
};

class trie{
    public:

    trienode *root; 
    trienode *temp;
    int num; // for number of words

    trie() {
        root = new trienode(); // initialize root node
        num = 0;
    }

    ~trie() {
        // recursively destroy the ROOT
        destroy(root);
    }

    void destroy(trienode* node) {
        if (!node) return;
        for (int i = 0; i < 26; ++i) {
            destroy(node->children[i]);
        }
        delete node;
    }
// all the functions, helpers included 
    void load();
    int countwords(trienode* current);
    bool search(std::string &word);
    void insert( std::string &word);
    int prefixnum(std::string &word);
    void erasenode(trienode* node, std::string &word, int depth);
    void erase(std::string &word);
    void printhelp(trienode *node, std::string &word);
    void printAll();
    void spellCheck(std::string& word);
    bool empty(trienode *node);
    void clear(trienode *node);
    void cleartrie();
    void size();
    int exit();

};
#endif