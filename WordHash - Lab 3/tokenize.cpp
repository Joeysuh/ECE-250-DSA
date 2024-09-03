#include "tokenize.h"
#include <iostream>
#include <string>
#include <forward_list>
#include <fstream>
#include <sstream>

unsigned int hash::hashFunc(std::string &str){ // working
    unsigned ans = 0;
    for (auto it = str.begin(); it != str.end(); it++){
        ans = ans * 29 + *it;
    }
    return ans % tablesize; // source: lab3 manual
}

// alphabetical checker, logic from piazza post TA comment
bool hash::isalpha(std::string &word){ // working
// iterate over the input word
    for (char string : word){
        if ((string < 'A' || string > 'Z') && (string < 'a' || string > 'z')){ 
            return false; // false since if anything here is true, it is not alphabetic
        }
    }
    return true; // is alpha
}

void hash::create(int size){ // working
    if ((size >= 1) && (size <= 256)){
        hashtable = new std::forward_list<std::pair<std::string, int>>[size]; // create a forward list with a pair of key value of specified size
        tablesize = size; // update tablesize global variable
        std::cout << "success" << std::endl;
    }
}

void hash::rehash(){
    // logic: to rehash, we calculate the load facto: wehn its greater than 0.8, we doule the capacity, move all our elements and delete old table
    unsigned int newtablesize = 2 * tablesize; // newtable size is the tablesize x2
    std::forward_list<std::pair<std::string, int>> *newtable = new std::forward_list<std::pair<std::string, int>>[newtablesize]; // new table initializaion
    tablesize = newtablesize; // update global table size

    // iterate through the size of the original array,
    for (unsigned int i{}; i < tokensarray.size(); i++){
        std::pair<std::string, int> entry(tokensarray[i], i + 1); // 1 indexing so create pair with string from tokensarray +1
        unsigned int index = hashFunc(tokensarray[i]); // compute index from hash function
        newtable[index].push_front(entry); // add to front of chain of new array
    }

    // delete old table, assign new table as the main table
    delete[] hashtable;
    hashtable = newtable;
}




bool hash::insert(std::string &word){ // calculate load factor and resize here since after we insert we should check for LF
    unsigned int index = hashFunc(word); // calculate index of word
    // check if word is in hash table by checking the index key val pair
    for (std::pair<std::string, int> &pair  : hashtable[index]){
        if (pair.first == word){ // if the pair key = word, we already inserted so return false
        std::cout << "failure" << std::endl;
            return false;
        }
    }
    // if word is alphabetic, we add word to tokens array
    if (isalpha(word)){
        tokensarray.push_back(word);
        std::cout << "success" << std::endl;
    } else { // not alphabetic so we return false
        std::cout << "failure" << std::endl;
        return false;
    }

    // create a new key value pair and insert to front of hashtable after passing all the checks
    std::pair<std::string, int> token(word, tokensarray.size());
    hashtable[index].push_front(token); // add to front of hashtable at calculated index
    //std::cout << "success" << std::endl;
    wordcount++; // update word count after an insert

    // calculate load factor after insert, resize if needed, we calculate after load insert or failed for ambiguous load factor checking.
    // static cast used to convert into double for accurate load factor calc
    double loadFactor = static_cast<double>(wordcount) / tablesize; // calculate LF
    if (loadFactor >= 0.8){
        rehash(); // resize for less collision reduction on next insert
        // std::cout << tablesize << std::endl;
    }
    return true;
}


auto original_cout = std::cout.rdbuf();

// redirect cout to a null stream
void redirect(){
    std::cout.rdbuf(nullptr);
}
// restore cout to the original destination
void restore(){
    std::cout.rdbuf(original_cout);
}

void hash::load(std::string &filename){
    // logic: use a boolean to check if inserted (update when insert), do a check, if inserted is true once, it will keep true so we can print success, else, fail
    redirect();
    bool inserted = false; 
   
    std::ifstream file(filename); // get input
    std::string word; // word insert in hash table

    if (!file.is_open()){
        return; // used for testing but actually deemed useful
    }
    // while we are not end of file...
    while (!file.eof()){ 
        file >> word; // read inputs
        if (insert(word)){ // if we can insert the word, the boolean is true
            inserted = true;
        }     
    }

    file.close(); // after file read, close file
    // check if any word has been inserted, if yes, we have success, else fail as per lab manual
    restore();
     if (inserted){
        std::cout << "success" << std::endl;
    } else {
        std::cout << "failure" << std::endl;
    }
    return;
}

void hash::token(std::string &word){
    // logic: calculate hash index, if we iterate the hash table and find the word print, else print -1
    int index = hashFunc(word); // calculate the hash index first of the word
    for (std::pair<std::string, int> &pair : hashtable[index]){ // iterate pairs at the index, still o(1) since we are not iterating the whole array, but the index of 
        if (pair.first == word){ // pair notation if the hash key = word, PRINT THE PAIRS INDEX (second since initialized second)
            std::cout << pair.second << std::endl; // print token of input word
            return;
        }
    }
    std::cout << "-1" << std::endl; // no word 
    return;
}

void hash::ret(unsigned int tokens){ // working
    if ((tokens <= tablesize && tokens >= 1) && (tokens < tokensarray.size() + 1)){  // if input is within tablesize bounds and is non-negative
        std::cout << tokensarray[tokens - 1] << std::endl; // 1 indexing, print the word
        return;
    }

    std::cout << "N/A" << std::endl; // else print N/A
}

void hash::tokenizeAll(std::string &word){
    // logic: use stringstream to parse through the inputs. While our entries are parsed, we can calculae each words hash.
    // iterate through the pairs and if we match a key to the entries, we update a boolean and PRINT
    std::stringstream parser(word); // get multiple inputs
    std::string entries; // entries for words
    bool found = false; 
    
    while (parser >> entries){ // while there are entries, calculate hash index, set found to false (nothing done yet), 
        int index = hashFunc(entries); // calculate hash index for each entry input
        found = false; // need to keep found = false, since we could enter for loop, update boolean, exit to last input, parse, not found and since we never print we have to print -1 but bool never updated
        for (auto &pair : hashtable[index]){
            if (pair.first == entries){ // if our inputs match in our table, we have a hit
                found = true; // update to true since we found words that match the hash index
                std::cout << pair.second << " ";
            }
        }
    
        if (!found){ // if not found, print series of -1
            std::cout << "-1 ";
        }
    }
    // new line for next input
    std::cout << std::endl;
    return;
}

void hash::retrieveAll(std::string &tokens){
    // Logic: parse all the entries, convert string to int, and check if the token is in the bounds of the hash table and an integer.
    // ff it's valid, start printing the word else, print "N/A".
    std::stringstream parser(tokens); // get tokens list input
    std::string entry; // entries string for isnert
    bool found = false; // variable to track if at least one valid word is found


    while (parser >> entry){// while we have entries
        unsigned int index = std::stoi(entry); // convert string entries to int index
        if (index >= 1 && index <= tokensarray.size()){ // if index is betweent he bounds of the token array, we know it's an entry
            found = true; // found indez so true
            std::cout << tokensarray[index - 1] << " "; // 1 indexing, 
        } else {
            std::cout << "N/A "; // NOT FOUND
        }
    }

    // if no valid words were found throught the whole string parse, print "N/A"
    if (!found){
        std::cout << "N/A";
    }

    std::cout << std::endl; // newline or next input
}

void hash::print(unsigned int k) {
    // check if input is out of bounds or if wordcount is zero
    if (wordcount == 0 || k >= tablesize) {
        return;
    }
    // check if the forward list at index k exists, if it doesnt do nothing, edge check incase emprt hash created and print called but above should handle
    if (hashtable[k].empty()) {
        return;
    }
    // all checks passed, iterate over the forward list at index k in the hashtable and print the keys
    for (auto& pair : hashtable[k]) {
        std::cout << pair.first << " ";
    }

    std::cout << std::endl; // print a newline after printing all the characters
}

// not necessary?????
int hash::exiting(){
    return 0;
}
