
#ifndef COMUNITY_MUSIC_PLAYER_ARTIST_H
#define COMUNITY_MUSIC_PLAYER_ARTIST_H
#include <string>
#include <vector>
#include "ListaSong.cpp"

class Artist {
private:
    string artist;
    ListaSong* list;
    Artist* next;
public:
    Artist(string);
    void addSong(Song*);
    void setNext(Artist*);
    string getArtist();
    Song* getSong(int);
    Artist* getNext();




};


#endif //COMUNITY_MUSIC_PLAYER_ARTIST_H
