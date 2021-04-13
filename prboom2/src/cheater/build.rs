use std::env;
use std::path::PathBuf;

fn main() {
    let mut src_dir = PathBuf::from(env::var("CARGO_MANIFEST_DIR").unwrap());
    src_dir.pop();
    cxx_build::bridge("src/lib.rs")
        .file("lib.rs.cc")
        .flag_if_supported("-std=c++17")
        .include(src_dir)
        .compile("cheater");

    println!("cargo:rerun-if-changed=src/lib.rs");
    println!("cargo:rerun-if-changed=lib.rs.cc");
    println!("cargo:rerun-if-changed=lib.rs.h");
}
