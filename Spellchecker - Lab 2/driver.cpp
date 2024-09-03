#include "trie.h"
#include <iostream>
#include <string>
#include <fstream>

int main(){
    std::string input;
    std::string word; // word or prefix idk

    trie trie;

    while (true){
        std::cin >> input;

        if (input == "load"){
            trie.load();
            std::cout << "success" << std::endl; 
        } else if (input == "c"){
            std::cin >> word;
            trie.prefixnum(word);
        } else if (input == "i" ){
            std::cin >> word;
            trie.insert(word);
        } else if (input == "e"){
            std::cin >> word;
            trie.erase(word);
        } else if (input == "p"){
            trie.printAll();
            // std::cout << std::endl; 
        } else if (input == "spellcheck"){
            std::cin >> word;
            trie.spellCheck(word);
        } else if (input == "empty"){
            if ( trie.empty(trie.root) == true){
                std::cout << "empty 1" << std::endl; 
            } else {
                std::cout << "empty 0" << std::endl; 
            }
        } else if (input == "clear"){
            trie.cleartrie();
        } else if (input == "size"){
            trie.size();
        } else if (input == "exit"){
            trie.exit();
            break; 
        }
    }
    return 0;
}