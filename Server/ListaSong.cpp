#include "iostream"
#include "Song.h"

class ListaSong {
private:
    Song* head;
    int size;
public:
    // Constructor
    ListaSong() : head(nullptr), size(0){}

    // Destructor
    ~ListaSong() {
        if (head == nullptr) return;

        Song* current = head;
        do {
            Song* next = current->getNext();
            delete current;
            current = next;
        } while (current != head);
    }

    // Método para agregar una nueva canción al final de la lista
    void addSong(std::string name, std::string address, std::string album, std::string artist,std::string genero) {
        Song* newSong = new Song(name, address, artist, album,genero);
        if (head == nullptr) {
            head = newSong;
            head->setNext(head);
            head->setPrev(head);
        } else {
            Song* last = head->getPrev();
            last->setNext(newSong);
            newSong->setPrev(last);
            newSong->setNext(head);
            head->setPrev(newSong);
        }
    }
    Song* getHeat(){
        return head;
    }

    // Método para imprimir todas las canciones en la lista
    void printSongs() {
        if (head == nullptr) {
            std::cout << "La lista de canciones está vacía." << std::endl;
            return;
        }

        Song* current = head;
        do {
            std::cout << "Nombre: " << current->getName() << ", Dirección: " << current->getAddress() << std::endl;
            current = current->getNext();
        } while (current != head);
    }
};