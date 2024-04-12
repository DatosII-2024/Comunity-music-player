#ifndef COMUNITY_MUSIC_PLAYER_SONG_H
#define COMUNITY_MUSIC_PLAYER_SONG_H

#include <string>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>


using namespace std;

class Song {
private:
    string id;
    string name;
    string album;
    string artist;
    string genero;
    int up;
    int down;
    string address;
    Song* next;
    Song* prev;
    bool full;

public:
    Song(string,string,string,string,string);
    void setNext(Song*);
    void setPrev(Song*);
    void setUp(int);
    void setDown(int);
    void setFull();
    void setName(string);
    void setAlbun(string);
    void setArtist(string);
    void setGenero(string);
    string getName();
    string getAddress();
    string getAlbum();
    string getArtist();
    string getGenero();
    int getUp();
    int getDown();
    bool getFull();
    Song* getNext();
    Song* getPrev();

    string generate_uuid();
};


#endif //COMUNITY_MUSIC_PLAYER_SONG_H
