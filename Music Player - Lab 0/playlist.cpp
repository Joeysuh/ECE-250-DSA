#include "playlist.h"
#include <iostream>
#include <string>
// name fix -- accidentally changed to john doe due to git name errors
//new c
// implement classes' member functions here...

using namespace std; 

// simple function for getting restricted entries
bool playlistcreator::restrictedsongs(const string &title, const string &artist) {
    return (title == "Baby" && artist == "Justin Bieber") || (title == "My Heart Will Go On");
}

// trivial method of setting the playlsit size
void playlistcreator::playlistsize(int size) {
    if (size >= 0) {
        // deallocate existing memory
        delete[] song;

        // update size
        playlist_size = size;

        // allocate new memory
        song = new songs[playlist_size];

        cout << "success" << endl;
            }
}
// iterate through the array and find if any index has both title and artist name. abstracted from addsong
bool playlistcreator::dupscheck( string &title, string &artist) {
    for (int i = 0; i < N; i++) { 
        if (song[i].getTitle() == title && song[i].getArtist() == artist) {
            return false;
        } 
    } 
    return true;
}

// addsong based the requirements, check edges like 0 size array and negative array
void playlistcreator::addsong() {
    string input;
    cin.ignore(); // ignore the newline character left by previous commands
    getline(cin, input);

    // find delimiter and combine title and artist together
size_t pos = input.find(';');
    if (pos != string::npos) {
        title = input.substr(0, pos);
        artist = input.substr(pos + 1);

    // Check if the playlist size is 0
    if (playlist_size <= 0) {
        cout << "can not insert " << title << ";" << artist << endl;
        return;
    }

    // check if the playlist is full
    if (N >= playlist_size) {
        cout << "can not insert " << title << ";" << artist << endl;
        return;
    }

    // check for restricted songs
    if (restrictedsongs(title, artist)) {
        cout << "can not insert " << title << ";" << artist << endl;
        return;
    }

    // check for duplicates based on both title and artist
    if (!dupscheck(title, artist)) {
        cout << "can not insert " << title << ";" << artist << endl;
        return;
    }

    // adding the song to the playlist
    song[N].setTitle(title);
    song[N].setArtist(artist);
    N++;
    cout << "success" << endl;
}

}


// only works when playlist size is valid
void playlistcreator::playsong(int n) {
    if (n >= 0 && n < N) {
        cout << "played " << n  << " " << song[n].getTitle() << ";" << song[n].getArtist() << endl;
    } else {
        cout << "can not play " << n << endl;
    }
}

void playlistcreator::erasesong( int n) {
    if (n >= 0 && n < N) { // can only run when array size is valid 
        for (int i = n; i < N - 1; i++) { 
            song[i] = song[i + 1]; // increment song postion
        }
        N--; // decrement size
        cout << "success" << endl;
    } else {
        cout << "can not erase " << n << endl;
    }
}

// safely deallocating the dynamic array
void playlistcreator::deallocate(){
    delete[] song;
    song = nullptr;
}
