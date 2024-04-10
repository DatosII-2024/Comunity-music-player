#include "Song.h"
#include "MusicPlayer.cpp"
#include "string"
#include "libconfig.h++"
#include <iostream>

int main() {
    libconfig::Config cfg;

    try {
        cfg.readFile("config.ini");
    }
    catch(const libconfig::FileIOException &fioex) {
        cerr << "Error al leer el archivo de configuración." << endl;
        return 1;
    }
    catch(const libconfig::ParseException &pex) {
        cerr << "Error de análisis en el archivo de configuración en línea "
                  << pex.getLine() << ": " << pex.getError() << endl;
        return 1;
    }

    const libconfig::Setting& root = cfg.getRoot();

    std::string key1, key2;
    if (!(root.lookupValue("General.Key1", key1) && root.lookupValue("General.Key2", key2))) {
        cerr << "No se encontraron las claves en el archivo de configuración." << endl;
        return 1;
    }

    cout << "Key1 = " << key1 << endl;
    cout << "Key2 = " << key2 << endl;

    return 0;
}
