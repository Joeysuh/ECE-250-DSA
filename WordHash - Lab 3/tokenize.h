#include <iostream>
#include <string>
#include <vector>
#include <forward_list>
#include <fstream>
#include <sstream>



class hash{
    private:

    unsigned int tablesize{}; // tablesize global variable for rehash calculation and boundary
    unsigned int wordcount{}; // wordcount to keep track of numer of words
    std::vector<std::string> tokensarray; // tokens array to store the key value pair
    std::forward_list<std::pair<std::string, int>>* hashtable; // forward list called hashtable storing a pair of string and ints


public: 
// default constructor
hash() = default;
~hash() {
    // deallocate memory for each list in the hashtable
    for (unsigned int i = 0; i < tablesize; ++i) {
        hashtable[i].clear();
    }
    // deallocate memory for the hashtable array
    delete[] hashtable;
}


// class functions and helpers
bool isalpha(std::string &word);
unsigned int hashFunc(std::string & str); // hash function to be used from lab manual
void create(int size);
void rehash();
bool insert(std::string &word);
void load(std::string& file); 
void token(std::string &word);
void ret(unsigned int tokens);
void tokenizeAll(std::string &word);
void retrieveAll(std::string &tokens);
void print(unsigned int k);
int exiting();
};
