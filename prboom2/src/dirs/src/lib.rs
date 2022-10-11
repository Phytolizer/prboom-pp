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
    let project_dirs = ProjectDirs::from("com", "phytolizer", "prboom++").unwrap();
    let d = project_dirs.config_dir();
    let d_str = d.to_str().unwrap();

    create_dir_all(d).unwrap();
    d_str.to_string()
}
