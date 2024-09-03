// include libraries here (STL not allowed)
#include <iostream>
#include <string>
#include "tokenize.h"


int main(){

hash hash;
std::string input; // command inputs
std::string word; // string inputs
int num{}; // numeric inputs

while (true){
    std::cin >> input;
    if (input == "create"){
        std::cin >> num;
        hash.create(num);
    } else if (input == "insert"){
        std::cin >> word;
        hash.insert(word);
    } else if (input == "load"){ 
        std::cin >> word;
        hash.load(word);
    } else if (input == "tok"){
        std::cin >> word;
        hash.token(word);
    } else if (input == "ret"){
        std::cin >> num; 
        hash.ret(num);
    } else if (input == "tok_all"){
        std::getline(std::cin, word);
        hash.tokenizeAll(word);
    } else if (input == "ret_all"){
        std::getline(std::cin, word);
        // pass the entire line to retrieveAll
        hash.retrieveAll(word);
    } else if (input == "print"){
        std::cin >> num;
        hash.print(num);
    } else if (input == "exit"){
        hash.exiting();
        return 0;
    }
}
  return 0;

}

