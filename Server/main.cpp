#include "Song.h"
#include "MusicPlayer.h"
#include "string"
#include "libconfig.h++"
#include <iostream>
#include "glog/logging.h"
#include <thread>
//#include "Socket.cpp"
int main(int argc, char *argv[]) {
    // Crear un hilo para ejecutar el socket
    //std::thread thread(Socket);

    // Esperar a que el hilo del socket termine
    //thread.join();

    google::InitGoogleLogging("Comunity_music_player");

    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
    gst_init(&argc, &argv);
    MusicPlayer player;
    return app->run(player);




    return 0;
}
