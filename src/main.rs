use fltk::{app, prelude::*, window, button}; // Importa los módulos necesarios

fn main() {
    let app = app::App::default();
    let mut win = window::Window::new(70, 60, 600, 500, "Community Music Player");

    let background_color = win.color(); // Obtener el color de fondo de la ventana

    let mut btn_upvote = button::Button::new(150, 30, 80, 40, "Vote up");
    btn_upvote.set_color(fltk::enums::Color::from_u32(0xFFE4C4));
    btn_upvote.set_label_size(15);

    let mut btn_downvote = button::Button::new(250, 30, 80, 40, "Vote down");
    btn_downvote.set_color(fltk::enums::Color::from_u32(0xFFE4C4));
    btn_downvote.set_label_size(15);

    let mut btn_playlist = button::Button::new(350, 30, 80, 40, "Playlist");
    btn_playlist.set_color(fltk::enums::Color::from_u32(0xFFE4C4));
    btn_playlist.set_label_size(15);

    let mut title = button::Button::new(10, 100, 100, 30, "Artista");
    title.clear_visible_focus();
    title.set_frame(fltk::enums::FrameType::FlatBox);
    title.set_label_size(15);

    // Establecer el color de fondo del botón al color de fondo de la ventana
    title.set_color(background_color);

    title.set_label_color(fltk::enums::Color::Black);

    win.end();
    win.show();

    app.run().unwrap();
}