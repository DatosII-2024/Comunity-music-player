//
// Created by erick on 15/02/24.
//

#ifndef COMUNITY_MUSIC_PLAYER_SONG_H
#define COMUNITY_MUSIC_PLAYER_SONG_H

using namespace std;

class Song {
private:
    string Name;
    string Album;
    string Artist;
    int Year;
    string Adress;
public:
    Song(string,string,string,int,string);
    string getName();
    string getAlbum();
    string getArtis();
    int getYear();
};


#endif //COMUNITY_MUSIC_PLAYER_SONG_H
