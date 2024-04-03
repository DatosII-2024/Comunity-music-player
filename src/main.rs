use fltk::{app, prelude::*, window, button}; 

fn main() {

    // Crea la ventana
    let app = app::App::default();
    let mut win = window::Window::new(70, 60, 600, 500, "Community Music Player");
    let background_color = win.color(); 

    
    //Botones 

    //Boton vote up
    let mut btn_upvote = button::Button::new(150, 30, 80, 40, "Vote up");
    btn_upvote.set_color(fltk::enums::Color::from_u32(0xFFE4C4));
    btn_upvote.set_label_size(15);

    //Boton vote down
    let mut btn_downvote = button::Button::new(250, 30, 80, 40, "Vote down");
    btn_downvote.set_color(fltk::enums::Color::from_u32(0xFFE4C4));
    btn_downvote.set_label_size(15);

    //Boton playlist
    let mut btn_playlist = button::Button::new(350, 30, 80, 40, "Playlist");
    btn_playlist.set_color(fltk::enums::Color::from_u32(0xFFE4C4));
    btn_playlist.set_label_size(15);


    //Titulos 

    //Titulo artista
    let mut title_artista = button::Button::new(50, 100, 100, 30, "Artista");
    title_artista.clear_visible_focus();
    title_artista.set_frame(fltk::enums::FrameType::FlatBox);
    title_artista.set_label_size(15);
    title_artista.set_color(background_color);
    title_artista.set_label_color(fltk::enums::Color::Black);

    //Titulo album
    let mut title_album = button::Button::new(160, 100, 100, 30, "Àlbum");
    title_album.clear_visible_focus();
    title_album.set_frame(fltk::enums::FrameType::FlatBox);
    title_album.set_label_size(15);
    title_album.set_color(background_color);
    title_album.set_label_color(fltk::enums::Color::Black);

    //Titulo canción
    let mut title_song = button::Button::new(270, 100, 100, 30, "Canción");
    title_song.clear_visible_focus();
    title_song.set_frame(fltk::enums::FrameType::FlatBox);
    title_song.set_label_size(15);
    title_song.set_color(background_color);
    title_song.set_label_color(fltk::enums::Color::Black);

    //Titulo genero
    let mut title_genero = button::Button::new(395, 100, 100, 30, "Gènero Musical");
    title_genero.clear_visible_focus();
    title_genero.set_frame(fltk::enums::FrameType::FlatBox);
    title_genero.set_label_size(15);
    title_genero.set_color(background_color);
    title_genero.set_label_color(fltk::enums::Color::Black);

    win.end();
    win.show();

    app.run().unwrap();
}
