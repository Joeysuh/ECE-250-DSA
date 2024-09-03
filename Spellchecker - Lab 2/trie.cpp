#include "trie.h"
#include <iostream>
#include <string>
#include <fstream>


// creditation: https://stackoverflow.com/questions/12184251/resetting-the-cout-after-redirection for helping me understand how to redirect and direct cout to the terminal and return it back after loading
// creditation: https://www.geeksforgeeks.org/stdstringpush_back-in-cpp/ for teaching me push_back and pop_back to use when passing by ref
auto original_cout = std::cout.rdbuf();

// redirect cout to a null stream
void redirect() {
    std::cout.rdbuf(nullptr);
}

// restore cout to the original destination
void restore() {
    std::cout.rdbuf(original_cout);
}


void trie::load() { // workings
    redirect(); 
    std::ifstream file("corpus.txt");
    std::string word;
    while (file >> word) {
        insert(word);
    }
    file.close(); 
    restore(); 
}


void trie::insert(std::string &word) { // working
    trienode* current = root;
// if search word comes up to be true (return false) then we failed to find
    if (search(word)) {
        std::cout << "failure" << std::endl;
        return;
    }

// for each loop to get index and iterate trie nodes, if we current children letter index is not present, create new  node and update current to travers (lab manual specifications)
    for (char c : word) {
        int loc = c - 'A';

        if (!current->children[loc]) {
            current->children[loc] = new trienode();
            if (!current->children[loc]) {

                return;
            }
        }
        current = current->children[loc];
    }
    // set isendofword to true for the last node of the inserted word
    current->isendofword = true;
    num++;
    std::cout << "success" << std::endl;
};

// search helper function to navigate on insert. easier to abstract instead of writing a search each time

bool trie::search(std::string& word){ // working
    trienode *current = root; 
    int length = word.length();
    // logicc: iterate trie while calculating index, if its not the current index then return false, implied else is true, can be seen in other functions when !search is called, if !search, then we know its fail to find.

    for (int i = 0; i < length; i++){
        int loc = word[i] - 'A';
        if (!current->children[loc]){
            current = current->children[loc]; 
            return false; 
        }
        current = current->children[loc];
    }
    return current->isendofword;
};

// count words function, recusively 
int trie::countwords(trienode* current){ // working
    int num = 0;
    // if current is end of word (boolean marked true from insert, then we know its end so increment global counter)
    if (current->isendofword) {
        num++; 
    } 
    // recursively call countwords to tally up everything.
    for (int i = 0; i < 26; i++) {
        if (current->children[i]) {
            num += countwords(current->children[i]);
        }
    }
    return num; 
}

int trie::prefixnum(std::string &prefix) { //working
    int length = prefix.length();
    trienode *current = root; 
// iterate trie, and calculate index, if our next is not null, go next, else then we didnt find so print NO FOUND
    for (int i = 0; i < length; i++) {
        int index = prefix[i] - 'A';
        trienode *next = current->children[index];
        if (!next) {
            std::cout << "not found" << std::endl; 
            return -1; 
        }
        current = next; 
    }
// canvrecursively print our function, sicnce after each count, it's another new trie.
    int count = countwords(current);
    std::cout << "count is " << count << std::endl;
    return count;
}

// erase helper function

void trie::erasenode(trienode* node, std::string &word, int depth) {
    int length = word.length();
    if (depth == length) {
        // reached the end of the word so mark the last node as not the end of a word
        node->isendofword = false;
        return;
    }

    int index = word[depth] - 'A';
    if (node->children[index] != nullptr) {
        // recursively traverse to the next node
        erasenode(node->children[index], word, depth + 1);

        // if the child node is not the end of another word and has no children, delete it
        if (empty(node->children[index]) && !node->children[index]->isendofword) {
            delete node->children[index];
            node->children[index] = nullptr;
        }
    }
}

void trie::erase(std::string& word) {
    // if we didn't find the word, then we print failure
    if (!search(word)) {
        std::cout << "failure" << std::endl;
        return;
    }
    // recursive call on erasenode, take in our root, input, and starting pos
    erasenode(root, word, 0);
// decrement global counter
    num--;
    std::cout << "success" << std::endl;
}


// print helper
void trie::printhelp(trienode *node, std::string &word){
    if (node->isendofword) {
        std::cout << word << " "; // print the word if it's the end of a word
    }
// iterate trie, if we have a node with a child, we calculate its index, push back amd then recursively print then popback to save its data
    for (int i = 0; i < 26; i++) {
        if (node->children[i]) {
            char character = 'A' + i;
            word.push_back(character); 
            printhelp(node->children[i], word); // recursively traverse the trie
            word.pop_back(); // remove the character after the recursive call returns
        }
    }
};

void trie::printAll() {
    std::string word = ""; // empty string for PBR
    printhelp(root, word); // call prin function, reaoson is we don't want to pass parameters in print in main, just execute.
    std::cout << std::endl;
}


void trie::spellCheck(std::string &word) {
    trienode* current = root;
    int length = word.length();
    std::string prefix; // initlaized to hold an empty string prefix
    //logic: 
    //traverse to the end of the word
    //if the next node is nullptr, run print recursively with the current prefix
    // if we spellcheck smth not relevant at all, no output

    // check if the word exists in the trie
    int firstindex = ((int)word[0]) - 'A'; // calculate first letter index
    if (firstindex < 0 || firstindex >= 26 || !current->children[firstindex]) {
        std::cout << std::endl;
        // if no matches for the first letter output nothing
        return;
    }

    for (int i{}; i < length; i++){
        int index = ((int) word[i]) - 65; // calculating all index for the word
        trienode* next = current->children[index];
        if (!next) {
            // If there's no next node, print the current prefix
            printhelp(current, prefix);
            std::cout << std::endl;
            return;
        }
        current = next;
        prefix.push_back(word[i]); // update prefix after updating current to next node
    }

// if we arent at end of word, print again recursively to see what was missed
    if (!current->isendofword){
        printhelp(current,word); 
        std::cout << std::endl; 
    } else {
        std::cout << "correct" << std::endl; 
    }
}


bool trie::empty(trienode *node) { // working
    bool isEmpty = true;
    for (int i = 0; i < 26; i++) { // iterate, if node child index then set empty as false since we found smth
        if (node->children[i]) {
            isEmpty = false;
            break;
        }
    }
    // check if boolean empty is now empty 1 or 0
    if (isEmpty){
        //std::cout << "empty 1" << std::endl;
    } else{ 
       // std::cout << "empty 0" << std::endl;
    }
    return isEmpty;
}




// helper to clear all of trie recursively
void trie::clear(trienode *node) {// working
    if (node == nullptr) {
        return;
    }
    // start deleting nodes by recursivley iterating trie and deleting
    for (int i{}; i < 26; ++i) {
        clear(node->children[i]);
    }
    delete node;
};

void trie::cleartrie() { //working
    clear(root); // recursively call clear function to clear trie
    root = new trienode(); 
    num = 0;
    std::cout << "success" << std::endl; 
}


void trie::size(){ //working
    std::cout << "number of words is " << num << std::endl; 
};

int trie::exit(){ // working
    return 0;
}