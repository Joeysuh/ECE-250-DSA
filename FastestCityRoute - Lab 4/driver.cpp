// include libraries here
#include <iostream>
#include <string>
#include "graph.h"


int main(){

    int a; //vertex a
    int b; // vertex b
    double d; // distance
    double s; // speed
    int A; // adjustment
    std::string input; // cin
    std::string filename; // for filename

    graph graph;

    while (true){
        std::cin >> input;
        if (input == "insert"){
  std::string line;
            std:: cin >> a >> b >> d >> s;
            graph.insert(a,b,d,s);
        } else if (input == "load"){
            std::cin >> filename; 
            graph.load(filename);
        } else if (input == "traffic"){
            std::cin >> a >> b >> A;
            graph.traffic(a,b,A);
        } else if (input == "update"){
            std::cin >> filename;
            graph.update(filename);
        } else if (input == "print"){
            std::cin >> a;
            graph.print(a);
        } else if (input == "delete"){
            std::cin >> a;
            graph.remove(a);
        } else if (input == "path"){
            std::cin >> a >> b;
            graph.path(a,b);
        } else if (input == "lowest"){
            std::cin >> a >> b;
            graph.lowest(a,b);
        } else if (input == "exit"){
            return 0;
        }
    }
    
return 0;
}
