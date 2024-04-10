#include "iostream"
#include "Song.h"
#include "string"

using namespace std;

// Constructor
Song::Song(string name, string address, string album, string artist, int year)
    : name(name), address(address), album(album), artist(artist), year(year), next(nullptr), prev(nullptr) {}

// Setters
void Song::setNext(Song* newNext) {
    next = newNext;
}
void Song::setPrev(Song* newPrev) {
    prev = newPrev;
}

// Getters
string Song::getName(){
    return name;
}

string Song::getAddress(){
    return address;
}

string Song::getAlbum(){
    return album;
}

string Song::getArtist(){
    return artist;
}

int Song::getYear(){
    return year;
}
Song* Song::getNext(){
    return next;
}

Song* Song::getPrev(){
    return prev;
}
