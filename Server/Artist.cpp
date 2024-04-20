#include "Artist.h"

Artist::Artist(string art)
        : artist(art){}

void Artist::addSong(Song * song) {
    list->addSong(song);
}
void Artist::setNext(Artist* art){
    next = art;
}
string Artist::getArtist() {
    return artist;
}
Song* Artist::getSong(int index) {
    Song* curr=  list->getHeat();
    for (int i= 0; i<index;i++){
        curr = curr->getNext();
    }
    return curr;
}
Artist* Artist::getNext() {
    return next;
}