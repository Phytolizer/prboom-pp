use std::env;
use std::path::PathBuf;

use bindgen::Builder;
use bindgen::CargoCallbacks;

fn main() {
    println!("cargo:rerun-if-changed=wrapper.h");

    let bindings = Builder::default()
        .header("wrapper.h")
        .parse_callbacks(Box::new(CargoCallbacks))
        .clang_args(&["-xc++", "-std=c++17"])
        .whitelist_type("default_t")
        .whitelist_type("sfxenum_t")
        .whitelist_type("weapontype_t")
        .whitelist_type("mobjtype_t")
        .whitelist_type("setup_menu_s")
        .whitelist_type("ss_types")
        .whitelist_function("strlen")
        .whitelist_function("M_LookupDefault")
        .whitelist_var("prboom_dir")
        .whitelist_var("numdefaults")
        .whitelist_var("defaults")
        .generate()
        .expect("Unable to generate bindings");

    let out_path = PathBuf::from(env::var("OUT_DIR").unwrap());
    bindings
        .write_to_file(out_path.join("bindings.rs"))
        .expect("Couldn't write bindings");
}
