fn main() {
    cxx_build::bridge("src/lib.rs")
        .file("lib.rs.cc")
        .flag_if_supported("-std=c++11")
        .compile("cheater");
    
    println!("cargo:rerun-if-changed=src/lib.rs");
    println!("cargo:rerun-if-changed=lib.rs.cc");
    println!("cargo:rerun-if-changed=lib.rs.h");
}
