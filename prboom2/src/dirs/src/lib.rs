use std::fs::create_dir_all;

use directories_next::ProjectDirs;

#[cxx::bridge]
mod ffi {
    extern "Rust" {
        #[namespace = "rust::dirs"]
        fn get_config_dir() -> String;
    }
}

pub fn get_config_dir() -> String {
    let d = ProjectDirs::from("com", "oncontentstop", "prboom++")
        .unwrap()
        .config_dir()
        .to_string_lossy()
        .to_string();

    create_dir_all(d.as_str()).unwrap();
    d
}
