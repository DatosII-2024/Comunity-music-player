use std::net::{TcpListener, TcpStream};
use std::io::{Read, Write};
use serde::{Deserialize, Serialize};
use std::sync::mpsc;

use crate::song::Song;






pub fn start_server(sender: mpsc::Sender<Song>) {
    std::thread::spawn(|| {
        if let Ok(listener) = TcpListener::bind("127.0.0.1:8080") {
            for stream in listener.incoming() {
                match stream {
                    Ok(mut stream) => {
                        let song = Song {
                            artist: "Artista Ejemplo".to_string(),
                            album: "Album Ejemplo".to_string(),
                            title: "Cancion Ejemplo".to_string(),
                            genre: "Genero Ejemplo".to_string(),
                        };
                        // Serializa la canción a JSON
                        let json_data = serde_json::to_string(&song).unwrap();

                        // Envía los datos al cliente
                        if let Err(e) = stream.write_all(json_data.as_bytes()) {
                            eprintln!("Error al enviar datos al cliente: {}", e);
                        }

                        // Cierra la conexión después de enviar los datos
                        if let Err(e) = stream.shutdown(std::net::Shutdown::Both) {
                            eprintln!("Error al cerrar la conexión: {}", e);
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
}
