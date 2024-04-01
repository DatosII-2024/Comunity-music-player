use eframe::{egui::{CentralPanel, CtxRef}, epi::App, run_native, NativeOptions};
use std::iter::FromIterator;

struct Headlines {
    articles: Vec<NewsCardData>,
}

impl Headlines {
    fn new() -> Headlines {
        let iter = (0..20).map(|a| NewsCardData {
            title: format!("title {}", a),
            desc: format!("desc {}", a),
        });
        Headlines {
            articles: Vec::from_iter(iter),
        }
    }
}

struct NewsCardData {
    title: String,
    desc: String,
}

impl App for Headlines {
    fn update(&mut self, ctx: &CtxRef, _frame: &mut eframe::epi::Frame<'_>) {
        CentralPanel::default().show(ctx, |ui| {
            for a in &self.articles {
                ui.label(&a.title);
                ui.label(&a.desc);
            }
        });
    }

    fn name(&self) -> &str {
        "Headlines"
    }
}

fn main() {
    let app = Headlines::new();
    let native_options = NativeOptions::default();
    run_native(Box::new(app), native_options);
}
