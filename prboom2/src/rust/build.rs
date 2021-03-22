use std::env;
use std::path::PathBuf;

use bindgen::Builder;
use bindgen::CargoCallbacks;

fn main() {
    println!("cargo:rerun-if-changed=wrapper.h");

    let bindings = Builder::default()
        .header("wrapper.h")
        .parse_callbacks(Box::new(CargoCallbacks))
        .generate()
        .expect("Unable to generate bindings");

    let out_path = PathBuf::from(env::var("OUT_DIR").unwrap());
    bindings
        .write_to_file(out_path.join("bindings.rs"))
        .expect("Couldn't write bindings");

    let crate_dir = env::var("CARGO_MANIFEST_DIR").unwrap();
    cbindgen::Builder::new()
        .with_crate(crate_dir)
        .with_namespace("rust")
        .with_include("sounds.hh")
        .with_pragma_once(true)
        .generate()
        .expect("Unable to generate bindings")
        .write_to_file("rust.hh");
}
