cmake_minimum_required(VERSION 3.17)

project(Comunity_music_player)

add_executable(Comunity_music_player Server/main.cpp
                Server/ListaSong.cpp
                Server/Song.cpp
                Server/Song.h
                Server/MusicPlayer.cpp
        Server/Socket.cpp)

target_link_libraries(Comunity_music_player
        config++
        glog)
