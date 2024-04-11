#include "Song.h"
#include "MusicPlayer.cpp"
#include "string"
#include "libconfig.h++"
#include <iostream>
#include "glog/logging.h"
#include <thread>
#include "Socket.cpp"

int main() {
    // Crear un hilo para ejecutar el socket
    std::thread thread(Socket);

    // Esperar a que el hilo del socket termine
    thread.join();

    /*libconfig::Config cfg;
    google::InitGoogleLogging("Comunity_music_player");

    try {
        cfg.readFile("/home/erick/Datos II/Comunity-music-player/Server/config.ini");
    }
    catch(const libconfig::FileIOException &fioex) {
        LOG(ERROR) << "Error al leer el archivo de configuración." << endl;
        return 1;
    }
    catch(const libconfig::ParseException &pex) {
        LOG(ERROR) << "Error de análisis en el archivo de configuración en línea "
                  << pex.getLine() << ": " << pex.getError() << endl;
        return 1;
    }

    const libconfig::Setting& root = cfg.getRoot();

    string key1, key2;
    if (!(root.lookupValue("General.Key1", key1) && root.lookupValue("General.Key2", key2))) {
        LOG(ERROR) << "No se encontraron las claves en el archivo de configuración." << endl;
        return 1;
    }

    LOG(INFO) << "Key1 = " << key1 << endl;
    LOG(INFO) << "Key2 = " << key2 << endl;*/

    return 0;
}
