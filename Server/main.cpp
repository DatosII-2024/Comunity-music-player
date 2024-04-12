#include "Song.h"
#include "MusicPlayer.h"
#include "string"
#include "libconfig.h++"
#include <iostream>
#include "glog/logging.h"
int main(int argc, char *argv[]) {

    google::InitGoogleLogging("Comunity_music_player");

    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
    gst_init(&argc, &argv);
    MusicPlayer player;
    return app->run(player);

    google::ShutdownGoogleLogging();
    return 0;
}
