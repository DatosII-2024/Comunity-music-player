#include "iostream"
#include "Song.h"
#include "string"

using namespace std;

// Constructor
Song::Song(string name, string address, string artist, string album,string genero)
    : name(name), address(address), album(album), artist(artist),genero(genero), up(0),down(0), next(nullptr), prev(nullptr) {
    id = generate_uuid();
}

// Setters
void Song::setNext(Song* newNext) {
    next = newNext;
}
void Song::setPrev(Song* newPrev) {
    prev = newPrev;
}
void Song::setUp(int u) {
    up = u;
}
void Song::setDown(int d) {
    down = d;
}
void Song::setFull() {
    full = true;
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
string Song::getGenero() {
    return genero;
}
int Song::getUp(){
    return up;
}
int Song::getDown() {
    return down;
}
Song* Song::getNext(){
    return next;
}

Song* Song::getPrev(){
    return prev;
}
bool Song::getFull() {
    return full;
}

void Song::setName(string n) {
    name = n;
}

void Song::setAlbun(string a) {
    album = a;
}

void Song::setArtist(string a) {
    artist = a;
}

void Song::setGenero(string g) {
    genero = g;
}

string Song::generate_uuid() {
    boost::uuids::uuid uuid = boost::uuids::random_generator()();
    return boost::uuids::to_string(uuid);
}


