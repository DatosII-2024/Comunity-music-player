use serde::{Deserialize, Serialize};

#[derive(Debug, Deserialize, Serialize)]
pub struct Song {
    pub artist: String,
    pub album: String,
    pub title: String,
    pub genre: String,
}
