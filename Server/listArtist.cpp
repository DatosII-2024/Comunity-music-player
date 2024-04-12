#include "Artist.h"

class listArtist{
private:
    Artist* head;
public:
    listArtist():head(nullptr){}

    ~listArtist(){
        if (head == nullptr) return;

        Artist* current = head;
        do {
            Artist* next = current->getNext();
            delete current;
            current = next;
        } while (current != head);
    }
};