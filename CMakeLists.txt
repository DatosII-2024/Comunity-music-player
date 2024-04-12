cmake_minimum_required(VERSION 3.17)

project(Comunity_music_player)

# Actualiza el estándar de C++ a C++17 para std::filesystem
set(CMAKE_CXX_STANDARD 17)

# Encuentra las dependencias
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)
pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0)

link_directories(
        ${GTKMM_LIBRARY_DIRS}
        ${GSTREAMER_LIBRARY_DIRS}
)

include_directories(
        ${GTKMM_INCLUDE_DIRS}
        ${GSTREAMER_INCLUDE_DIRS}
)

add_executable(Comunity_music_player
                Server/main.cpp
                Server/ListaSong.cpp
                Server/Song.cpp
                Server/Song.h
                Server/MusicPlayer.cpp
                Server/Socket.cpp
)

target_link_libraries(Comunity_music_player
        config++
        glog
        ${GTKMM_LIBRARIES}
        ${GSTREAMER_LIBRARIES}
)

# Enlaza con stdc++fs si es necesario (GCC < 9)
if (CMAKE_COMPILER_IS_GNUCC AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9)
    target_link_libraries(MiReproductorDeMusica stdc++fs)
endif()