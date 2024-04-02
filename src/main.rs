use fltk::{app, prelude::*, window, button}; // Importa el módulo button

fn main() {
    let app = app::App::default();
    let mut win = window::Window::new(100, 100, 400, 300, "Community Music Player");

    let mut btn = button::Button::new(160, 120, 80, 40, "Botón"); // Crea un nuevo botón
    btn.set_color(fltk::enums::Color::from_u32(0xFFE4C4)); // Establece el color del botón (Opcional)
    btn.set_label_size(20); // Establece el tamaño del texto del botón (Opcional)

    win.end();
    win.show();

    app.run().unwrap();
}

