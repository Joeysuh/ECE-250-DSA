// new c
#include <string>
#include <iostream>
using namespace std;

class songs {
    std::string title{};
    std::string artist{};
    int playlist_size{};

public:
    songs() = default;
    songs(const std::string& t, const std::string& a, int size) // using copy constructors to get title, artist, and playlist sizes.
        : title(t), artist(a), playlist_size(size) {}

    songs(const songs& other)
        : title(other.title), artist(other.artist), playlist_size(other.playlist_size) {}

    songs& operator=(const songs& other) { // assigning values of same type to other variable. enables freedom of string chains
        if (this != &other) {
            title = other.title;
            artist = other.artist;
        }
        return *this;
    }
    //getters and setters
    std::string getTitle() const {
     return title; 
     }
    std::string getArtist() const { 
        return artist; 
    }

    void setTitle(const std::string& t){ 
        title = t; 
    }
    void setArtist(const std::string& a){ 
        artist = a; 
    }

};


class playlistcreator {
    songs* song;           
    int N;                 
    int playlist_size{};     // maximum playlist size
    string title;
    string artist;
public:
    playlistcreator() = default; 
    playlistcreator(int size) : N(0), playlist_size(size) { 
    if (size < 0) {
        return;
    }
    song = new songs[playlist_size]; // array allocation
    }
    ~playlistcreator() {
        delete[] song;    //  cleanup of allocated memory
    }
// class functions
    bool restrictedsongs(const string &title, const string &artist);
    bool dupscheck( string &title, string &artist);
    void playlistsize(int size);
    void addsong();
    void playsong(int n);
    void erasesong( int n);
    void deallocate();


};

// name fix -- accidentally changed to john doe due to git name errors

