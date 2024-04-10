#ifndef COMUNITY_MUSIC_PLAYER_SONG_H
#define COMUNITY_MUSIC_PLAYER_SONG_H

#include <string>

using namespace std;

class Song {
private:
    string name;
    string address;
    string album;
    string artist;
    int year;
    Song* next;
    Song* prev;

public:
    Song(string,string,string,string,int);
    void setNext(Song*);
    void setPrev(Song*);
    string getName();
    string getAddress();
    string getAlbum();
    string getArtist();
    int getYear();
    Song* getNext();
    Song* getPrev();
};


#endif //COMUNITY_MUSIC_PLAYER_SONG_H
