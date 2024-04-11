#include "Song.h"
#include <iostream>

#include <glog/logging.h>


class MusicPlayer {
private:
    Song* current;
    bool isPlaying;


public:
    // Constructor
    MusicPlayer(Song* song) : current(song), isPlaying(false)  {google::InitGoogleLogging("Comunity_music_player");}

    // Destructor

    // Método para preparar la reproducción
    void ready() {
        if (!isPlaying) {
            if (true) {
                LOG(ERROR) << "Error loading " << current->getName() << std::endl;
            }
        } else {
            LOG(INFO) << "Ya se encuentra en reproducción." << std::endl;
        }
        while (getStatus()){

        }
    }

    // Método para reproducir o pausar la canción
    void play() {
        if (!isPlaying) {

            isPlaying = true;
            LOG(INFO) << "Reproduciendo la canción." << std::endl;
        } else {
            isPlaying = false;

            LOG(INFO) << "Pausando la reproducción." << std::endl;
        }
    }

    bool getStatus(){
        return true;
    }

    // Método para avanzar a la siguiente canción
    void next() {
        isPlaying = false;
        current = current->getNext();
        LOG(INFO) << "Reproduciendo la siguiente canción." << std::endl;
        ready();
    }

    // Método para retroceder a la canción anterior
    void previous() {
        current = current->getPrev();
        LOG(INFO) << "Reproduciendo la canción anterior." << std::endl;
        ready();
    }
    // Método para detener la reproducción y liberar los recursos de audio
    void cleanup() {

    }
};