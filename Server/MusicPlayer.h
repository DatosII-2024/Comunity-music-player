#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H

#include <gtkmm.h>
#include <gst/gst.h>
#include <vector>
#include <string>
#include <filesystem>
#include <gst/tag/tag.h>
#include "ListaSong.cpp"
#include "Song.h"
#include <thread>
#include "Socket.cpp"
#include <random>
#include "iostream"

namespace fs = std::filesystem;

class MusicPlayer : public Gtk::Window {
public:
    MusicPlayer();
    virtual ~MusicPlayer();

protected:
    // Signal handlers:
    void on_button_play_clicked();
    void on_button_pause_clicked();
    void on_button_next_clicked();
    void on_button_previous_clicked();
    void on_button_delete_clicked();
    void on_button_comunity_clicked();
    void on_scale_progress_value_changed();
    void on_volume_value_changed();
    bool on_timeout(); // Actualiza la barra de progreso

    // Helper functions:
    void play_song(const std::string& filepath);
    void update_song_info(); // Actualiza la información de la canción actual en la UI
    void load_songs_from_directory(const std::string& path); // Carga canciones desde un directorio
    void create_playList(std::vector<std::string>);

    // Member widgets:
    Gtk::Box m_VBoxMain, m_VBoxButtons, m_HBoxTop, m_HBoxBottom;
    Gtk::Button m_ButtonPrevious{"↞"};
    Gtk::Button m_ButtonPlay{"▶"};
    Gtk::Button m_ButtonPause{"〓"};
    Gtk::Button m_ButtonNext{"↠"};
    Gtk::Button m_ButtonDelete{"Delete"};
    Gtk::Button m_ButtonComunity{"Comunity"};
    Gtk::Label m_LabelStartTime{"00:00"};
    Gtk::Label m_LabelEndTime{"00:00"};
    Gtk::Scale m_ScaleProgress{Gtk::ORIENTATION_HORIZONTAL};
    Gtk::Scale m_VolumeScale{Gtk::ORIENTATION_VERTICAL};
    Gtk::Label m_LabelArtistName;
    Gtk::Label m_LabelSongTitle;
    Gtk::Label m_LabelAlbumName;
    Gtk::Label m_LabelSongGener;

    // GStreamer elements:
    GstElement *pipeline;
    bool playing = FALSE;

    // Playlist management:
    ListaSong* playList = new ListaSong(); //Listad de canciones en objetos Song
    Song* current = nullptr; // Objetos song con canciones
};

#endif // MUSIC_PLAYER_H
