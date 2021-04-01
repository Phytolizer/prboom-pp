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

    println!("Writing input bindings");
    let out_path = PathBuf::from(env::var("OUT_DIR").unwrap());
    bindings
        .write_to_file(out_path.join("bindings.rs"))
        .expect("Couldn't write bindings");

    let crate_dir = env::var("CARGO_MANIFEST_DIR").unwrap();
    println!("Writing output bindings");
    cbindgen::generate(crate_dir)
        .expect("Unable to generate output header")
        .write_to_file("rust.hh");
}
