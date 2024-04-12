use fltk::{app, prelude::*, window, button, frame};
use std::net::{TcpListener, TcpStream};
use std::sync::mpsc;
use std::thread;
use std::io::{Read, Write};
use serde::{Deserialize, Serialize};
mod server;
use server::start_server;
mod song;
use song::Song;

fn main() {
    // Crea la ventana
    let app = app::App::default();
    let mut win = window::Window::new(70, 60, 600, 500, "Community Music Player");
    let background_color = win.color();

    // Botones
    // Boton vote up
    let mut btn_upvote = button::Button::new(150, 60, 80, 40, "Vote up");
    btn_upvote.set_color(fltk::enums::Color::from_u32(0xFFE4C4));
    btn_upvote.set_label_size(15);

        // Lógica de voto hacia arriba
        btn_upvote.handle(move |_btn_upvote, _ev| {

            // Envía el voto hacia arriba y lo conecta
            if let Ok(mut stream) = TcpStream::connect("127.0.0.1:8080") {
               
                // manda el comando que diga que se presionò exactamente es
                let command = "vote_up";
                // Envía el comando al servidor a través del socket
                let _ = stream.write_all(command.as_bytes());
            }
            // Retorna true para indicar que el evento ha sido manejado
            true
        });

    let mut btn_downvote = button::Button::new(250, 60, 80, 40, "Vote down");
    btn_downvote.set_color(fltk::enums::Color::from_u32(0xFFE4C4));
    btn_downvote.set_label_size(15);

        // Lógica de voto hacia abajo
        btn_downvote.handle(move |_btn_downvote, _ev| {

            // Envía el voto hacia abajo y lo conecta
            if let Ok(mut stream) = TcpStream::connect("127.0.0.1:8080") {

                // manda el comando que diga que se presionó exactamente este botón
                let command = "vote_down";
        
                // Envía el comando al servidor a través del socket
                let _ = stream.write_all(command.as_bytes());
    }
            // Retorna true para indicar que el evento ha sido manejado
            true
        });


    let mut btn_playlist = button::Button::new(350, 60, 80, 40, "Playlist");
    btn_playlist.set_color(fltk::enums::Color::from_u32(0xFFE4C4));
    btn_playlist.set_label_size(15);



    // Titulos 
    let mut title_label = frame::Frame::new(10, 10, 580, 40, "Community Music Player");
    title_label.set_label_size(30);
    // Titulo artista
    let mut title_artista = button::Button::new(50, 100, 100, 30, "Artista");
    title_artista.clear_visible_focus();
    title_artista.set_frame(fltk::enums::FrameType::FlatBox);
    title_artista.set_label_size(15);
    title_artista.set_color(background_color);
    title_artista.set_label_color(fltk::enums::Color::Black);

    let mut title_album = button::Button::new(160, 100, 100, 30, "Álbum");
    title_album.clear_visible_focus();
    title_album.set_frame(fltk::enums::FrameType::FlatBox);
    title_album.set_label_size(15);
    title_album.set_color(background_color);
    title_album.set_label_color(fltk::enums::Color::Black);

    let mut title_song = button::Button::new(270, 100, 100, 30, "Canción");
    title_song.clear_visible_focus();
    title_song.set_frame(fltk::enums::FrameType::FlatBox);
    title_song.set_label_size(15);
    title_song.set_color(background_color);
    title_song.set_label_color(fltk::enums::Color::Black);

    let mut title_genero = button::Button::new(395, 100, 100, 30, "Género Musical");
    title_genero.clear_visible_focus();
    title_genero.set_frame(fltk::enums::FrameType::FlatBox);
    title_genero.set_label_size(15);
    title_genero.set_color(background_color);
    title_genero.set_label_color(fltk::enums::Color::Black);


    // Almacena una referencia al objeto de la aplicación
    let app_ref = app.clone();

    let (sender, receiver) = mpsc::channel();

    start_server(sender.clone());

    // Hilo para actualizar la interfaz gráfica con los datos de la canción
    thread::spawn(move || {
        // Define los widgets de la interfaz gráfica dentro del hilo
        let mut title_frame = frame::Frame::new(50, 100, 500, 30, "");
        let mut artist_frame = frame::Frame::new(50, 150, 500, 30, "");
        let mut album_frame = frame::Frame::new(50, 200, 500, 30, "");
        let mut genre_frame = frame::Frame::new(50, 250, 500, 30, "");

        if let Ok(listener) = TcpListener::bind("127.0.0.1:8080") {
            for stream in listener.incoming() {
                match stream {
                    Ok(mut stream) => {
                        // Manejo del stream del socket
                        let mut buffer = [0; 1024];
                        match stream.read(&mut buffer) {
                            Ok(n) => {
                                // Convertir los datos recibidos a una estructura Song
                                if let Ok(song) = serde_json::from_slice::<Song>(&buffer[..n]) {
                                    // Enviar la canción al hilo principal a través del canal
                                    if sender.send(song).is_err() {
                                        eprintln!("Error al enviar la canción al hilo principal");
                                    }
                                }
                            },
                            Err(e) => {
                                eprintln!("Error de lectura: {}", e);
                            }
                        }
                    },
                    Err(e) => {
                        eprintln!("Error de conexión: {}", e);
                    }
                }
            }
        } else {
            eprintln!("Error al iniciar el servidor");
        }
    });

    // Hilo principal: actualiza la interfaz gráfica con los datos recibidos del servidor
    while app.wait() {
        // Recibe la canción del canal y actualiza la interfaz gráfica
        if let Ok(song) = receiver.try_recv() {
            app::add_idle(move || {
                let mut title_frame = frame::Frame::new(50, 100, 500, 30, ""); // Nueva instancia de title_frame
                let mut artist_frame = frame::Frame::new(50, 150, 500, 30, "");
                let mut album_frame = frame::Frame::new(50, 200, 500, 30, "");
                let mut genre_frame = frame::Frame::new(50, 250, 500, 30, "");

                title_frame.set_label(&song.title);
                artist_frame.set_label(&song.artist);
                album_frame.set_label(&song.album);
                genre_frame.set_label(&song.genre);
            });
        }
    }

    // Muestra la ventana de la interfaz gráfica
    win.make_resizable(true);
    win.end();
    win.show();

    app.run().unwrap();
}
 
