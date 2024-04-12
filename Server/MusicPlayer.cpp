#include "MusicPlayer.h"
#include "glog/logging.h"

MusicPlayer::MusicPlayer() {
    set_title("Music Player");
    set_default_size(600, 800);

    // Organiza los widgets en la ventana utilizando boxes:
    m_VBoxMain.set_orientation(Gtk::ORIENTATION_VERTICAL);
    add(m_VBoxMain);

    // Configura la barra de progreso:
    m_ScaleProgress.set_draw_value(false); // Ocultar el valor numérico de la barra de progreso
    m_ScaleProgress.set_range(0.0, 100.0); // El rango debería ajustarse según la duración de la canción

    // Configura las cajas horizontales para el tiempo y la barra de progreso:
    m_HBoxTop.pack_start(m_LabelStartTime);
    m_HBoxTop.pack_end(m_LabelEndTime);

    // Configura la caja horizontal para los botones:
    m_VBoxButtons.pack_start(m_ButtonPrevious);
    m_VBoxButtons.pack_start(m_ButtonPlay);
    m_VBoxButtons.pack_start(m_ButtonPause);
    m_VBoxButtons.pack_start(m_ButtonNext);
    m_VBoxButtons.pack_start(m_ButtonDelete);
    m_VBoxButtons.pack_start(m_ButtonComunity);
    m_VBoxButtons.set_homogeneous(true); // Hace que todos los botones tengan el mismo ancho

    // Configura el slider de volumen:
    m_VolumeScale.set_range(0.0, 1.0); // Rango de volumen entre 0.0 y 1.0
    m_VolumeScale.set_value(1.0); // Valor inicial de volumen al máximo
    m_VolumeScale.set_inverted(true); // Invertir la dirección del slider
    m_VolumeScale.set_size_request(100, -1); // Tamaño fijo del slider

    // Añade el slider de volumen a la caja horizontal de abajo:
    m_HBoxBottom.pack_start(m_VolumeScale);

    // Añade las cajas horizontales y la barra de progreso a la caja vertical principal:
    m_VBoxMain.pack_start(m_LabelSongTitle);
    m_VBoxMain.pack_start(m_LabelArtistName);
    m_VBoxMain.pack_start(m_LabelAlbumName);
    m_VBoxMain.pack_start(m_LabelSongGener);
    m_VBoxMain.pack_start(m_HBoxTop);
    m_VBoxMain.pack_start(m_ScaleProgress);
    m_VBoxMain.pack_start(m_HBoxBottom);
    m_HBoxBottom.pack_start(m_VBoxButtons);
    m_VBoxMain.pack_start(m_LabelSong1);
    m_VBoxMain.pack_start(m_LabelSong2);
    m_VBoxMain.pack_start(m_LabelSong3);
    m_VBoxMain.pack_start(m_LabelSong4);
    m_VBoxMain.pack_start(m_LabelSong5);
    m_VBoxMain.pack_start(m_LabelSong6);
    m_VBoxMain.pack_start(m_LabelSong7);
    m_VBoxMain.pack_start(m_LabelSong8);
    m_VBoxMain.pack_start(m_LabelSong9);
    m_VBoxMain.pack_start(m_LabelSong10);



    // Conecta las señales de los botones con sus manejadores de eventos:
    m_ButtonPlay.signal_clicked().connect(sigc::mem_fun(*this, &MusicPlayer::on_button_play_clicked));
    m_ButtonPause.signal_clicked().connect(sigc::mem_fun(*this, &MusicPlayer::on_button_pause_clicked));
    m_ButtonNext.signal_clicked().connect(sigc::mem_fun(*this, &MusicPlayer::on_button_next_clicked));
    m_ButtonPrevious.signal_clicked().connect(sigc::mem_fun(*this, &MusicPlayer::on_button_previous_clicked));
    m_ButtonDelete.signal_clicked().connect(sigc::mem_fun(*this,&MusicPlayer::on_button_delete_clicked));
    m_ButtonComunity.signal_clicked().connect(sigc::mem_fun(*this, &MusicPlayer::on_button_comunity_clicked));
    m_ScaleProgress.signal_value_changed().connect(sigc::mem_fun(*this, &MusicPlayer::on_scale_progress_value_changed));
    // Conecta la señal del slider de volumen con su manejador de evento:
    m_VolumeScale.signal_value_changed().connect(sigc::mem_fun(*this, &MusicPlayer::on_volume_value_changed));
    Glib::signal_timeout().connect(sigc::mem_fun(*this, &MusicPlayer::on_timeout), 1000); // Update progress bar every second

    show_all_children();
    load_songs_from_directory("/home/erick/music");
}

MusicPlayer::~MusicPlayer() {
    if (pipeline) {
        gst_element_set_state(pipeline, GST_STATE_NULL);
        gst_object_unref(GST_OBJECT(pipeline));
    }
}

void MusicPlayer::on_button_play_clicked() {
    GstState state;
    gst_element_get_state(pipeline, &state, NULL, 0);

    // Si la canción está pausada, reanuda la reproducción.
    if (state == GST_STATE_PAUSED) {
        gst_element_set_state(pipeline, GST_STATE_PLAYING);
        playing = true;
    } else if (!playing && current!= nullptr && state != GST_STATE_PLAYING) {
        // Inicia la reproducion
        play_song(current->getAddress());
    } else {
        // Inicia la reproducion
        LOG(ERROR) << "Error al intentar reproducir la canción";
    }
}

void MusicPlayer::on_button_pause_clicked() {
    if (playing) {
        gst_element_set_state(pipeline, GST_STATE_PAUSED);
        playing = false;
    } else {
        LOG(ERROR) << "Error al intentar pausar la canción";
    }
}

void MusicPlayer::on_button_next_clicked() {
    if (current->getNext()!= nullptr) {
        current = current->getNext();
        play_song(current->getAddress());
    }else {
        LOG(ERROR) << "Error al intentar reproducir la siguiente canción";
    }
}

void MusicPlayer::on_button_previous_clicked() {
    if (current->getPrev()!= nullptr) {
        current = current->getPrev();
        play_song(current->getAddress());
    }else {
        LOG(ERROR) << "Error al intentar reproducir la canción anterior";
    }
}
void MusicPlayer::on_button_delete_clicked(){
    current->getPrev()->setNext(current->getNext());
    current->getNext()->setPrev(current->getPrev());
    Song* por = current->getNext();
    delete current;
    current = por;
    play_song(current->getAddress());
}
void MusicPlayer::on_button_comunity_clicked() {
    // Crear un hilo para ejecutar el socket
    std::thread thread(&Socket::run);

    // Esperar a que el hilo del socket termine
    thread.detach();
}

void MusicPlayer::play_song(const std::string& filepath) {
    if (pipeline) {
        gst_element_set_state(pipeline, GST_STATE_NULL);
        gst_object_unref(GST_OBJECT(pipeline));
    }

    std::string uri = "file://" + filepath;
    pipeline = gst_parse_launch(("playbin uri=" + uri).c_str(), NULL);
    if (!pipeline) {
        LOG(ERROR) << "Error al crear el pipeline de GStreamer";
        return;
    }
    gst_element_set_state(pipeline, GST_STATE_PLAYING);
    playing = true;

    // Espera a que GStreamer prepare la media y pueda reportar la duración
    gst_element_get_state(pipeline, NULL, NULL, GST_CLOCK_TIME_NONE);

    gint64 duration = 0;
    if (gst_element_query_duration(pipeline, GST_FORMAT_TIME, &duration)) {
        // Convierte la duración a segundos
        int duration_seconds = GST_TIME_AS_SECONDS(duration);
        int minutes = duration_seconds / 60;
        int seconds = duration_seconds % 60;
        m_LabelEndTime.set_text(Glib::ustring::compose("%1:%2", minutes, seconds < 10 ? "0" + std::to_string(seconds) : std::to_string(seconds)));
    }

    update_song_info();
}

bool MusicPlayer::on_timeout() {
    if (!pipeline || !playing) return true; // Continuar llamando la función si no está reproduciendo

    gint64 pos = 0;
    if (gst_element_query_position(pipeline, GST_FORMAT_TIME, &pos)) {
        // Convierte la posición a segundos
        int pos_seconds = GST_TIME_AS_SECONDS(pos);
        int minutes = pos_seconds / 60;
        int seconds = pos_seconds % 60;
        m_LabelStartTime.set_text(Glib::ustring::compose("%1:%2", minutes, seconds < 10 ? "0" + std::to_string(seconds) : std::to_string(seconds)));

        // También actualiza el valor del slider de progreso si deseas
        gint64 duration = 0;
        if (gst_element_query_duration(pipeline, GST_FORMAT_TIME, &duration)) {
            double newPos = (double)pos / (double)duration;
            m_ScaleProgress.set_value(newPos * 100.0);
        }
    }

    return true; // Mantener la llamada a timeout activa
}

void MusicPlayer::update_song_info() {
    if (!current->getFull()) {
        GstTagList* tags = NULL;
        g_signal_emit_by_name(pipeline, "get-audio-tags", 0, &tags);
        if (tags) {
            gchar* title = NULL;
            gchar* artist = NULL;
            gchar* album = NULL;
            gchar* genre = NULL;

            if (gst_tag_list_get_string(tags, GST_TAG_TITLE, &title)) {
                current->setName(std::string(title));
                g_free(title);
            } else {
                current->setName("Unknown");
            }

            if (gst_tag_list_get_string(tags, GST_TAG_ARTIST, &artist)) {
                current->setArtist(std::string(artist));
                g_free(artist);
            } else {
                current->setArtist("Unknown");
            }

            if (gst_tag_list_get_string(tags, GST_TAG_ALBUM, &album)) {
                current->setAlbun(std::string(album));
                g_free(album);
            } else {
                current->setAlbun(" Unknown");
            }
            if (gst_tag_list_get_string(tags, GST_TAG_GENRE, &genre)) {
                current->setGenero(std::string(genre));
                g_free(genre);
            } else {
                current->setGenero(" Unknown");
            }

            gst_tag_list_unref(tags);
        }
        current->setFull();
    }
    for (int s=0; s<10;s++ ){
        current = current->getNext();
        if(s==0){
            m_LabelSong1.set_text(current->getName());
        }else if(s==1){
            m_LabelSong2.set_text(current->getName());
        }else if(s==2){
            m_LabelSong3.set_text(current->getName());
        }else if(s==3){
            m_LabelSong4.set_text(current->getName());
        }else if(s==4){
            m_LabelSong5.set_text(current->getName());
        }else if(s==5){
            m_LabelSong6.set_text(current->getName());
        }else if(s==6){
            m_LabelSong7.set_text(current->getName());
        }else if(s==7){
            m_LabelSong8.set_text(current->getName());
        }else if(s==8){
            m_LabelSong9.set_text(current->getName());
        }else if(s==9){
            m_LabelSong10.set_text(current->getName());
        }
    }
    m_LabelSongTitle.set_text("Title: " + current->getName());
    m_LabelArtistName.set_text("Artist: " + current->getArtist());
    m_LabelAlbumName.set_text("Album: " + current->getAlbum());
    m_LabelSongGener.set_text("Gener: " + current->getGenero());
    LOG(INFO)<<current->getId();

}

void MusicPlayer::on_scale_progress_value_changed() {
    if (!pipeline || !playing) return;
    // Calcula el nuevo tiempo basado en la posición del slider y realiza un seek
    gint64 duration;
    if (gst_element_query_duration(pipeline, GST_FORMAT_TIME, &duration)) {
        gdouble new_value = m_ScaleProgress.get_value();
        gint64 new_time = (gint64)((new_value / 100.0) * (gdouble)duration);
        gst_element_seek_simple(pipeline, GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH, new_time);
    }

}

void MusicPlayer::on_volume_value_changed() {
    if (pipeline) {
        gdouble volume = m_VolumeScale.get_value();
        g_object_set(pipeline, "volume", volume, NULL);
    }
}

void MusicPlayer::load_songs_from_directory(const std::string& path) {
    for (const auto& entry : fs::directory_iterator(path)) {
        if (entry.is_regular_file() && entry.path().extension() == ".mp3") {
            Song* newSong = new Song("", entry.path().string(), "", "","");
            playList->addSong(newSong);
        }
    }
    current = playList->getHeat();
}

