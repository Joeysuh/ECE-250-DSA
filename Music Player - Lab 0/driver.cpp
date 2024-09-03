    // include libraries here (STL not allowed)
    // name fix -- accidentally changed to john doe due to git name errors
// new c
#include <iostream>
#include <string>
#include "playlist.h"
using namespace std;

    int main(int argc, char *argv[]){
        int m{};
    playlistcreator Playlist(m);
        char in{};
        int n; 
        int g; 

        while (cin >> in) {
            switch (in) {
                case 'm':
                     cin >> m;
                     Playlist.playlistsize(m);
                    break;
                case 'i':
                     Playlist.addsong();
                     break;
                case 'p':
                    cin >> n;
                    Playlist.playsong(n);
                    break;
                case 'e':
                    cin >> g;
                    Playlist.erasesong(g);
                    break;
                case 'd':
                    return 0;
            }
        }

        Playlist.deallocate();

        return 0;
    }