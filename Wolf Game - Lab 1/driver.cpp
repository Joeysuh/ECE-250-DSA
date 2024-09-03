// include libraries here (STL not allowed)
#include <iostream>
#include <string>
#include "game.h"
#include <cmath>

using namespace std; 

int main(){
    // your code goes here... 
    playerlist game;
    std::string in;
    double x{};
    double y{};
    double t{};
    double distance{};

    while (cin >> in){
    if ( in == "SPAWN") {
        cin >> x;
        cin >> y;
        game.SPAWN(x,y);
    } else if (in == "TIME"){
        cin >> t;
        game.TIME(t);
    } else if ( in == "LUNCH"){
        game.LUNCH();
    } else if ( in == "NUM"){
        game.NUM();
    } else if (in == "PRT"){
        cin >> distance;
        game.PRT(distance);
    } else if (in == "OVER"){
        game.OVER();
        return 0; 
    }
    }
    }       