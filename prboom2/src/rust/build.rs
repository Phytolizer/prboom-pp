use std::env;
use std::path::PathBuf;

use bindgen::Builder;
use bindgen::CargoCallbacks;

fn main() {
    println!("cargo:rerun-if-changed=wrapper.h");

    let build_dir = env::var("BUILD_DIR").unwrap_or_else(|_| "../../../build".into());

    let bindings = Builder::default()
        .header("wrapper.h")
        .parse_callbacks(Box::new(CargoCallbacks))
        .clang_args(&["-xc++", "-std=c++17", &format!("-I{}", build_dir)])
        .detect_include_paths(true)
        .whitelist_type("default_t")
        .whitelist_type("sfxenum_t")
        .whitelist_type("weapontype_t")
        .whitelist_type("mobjtype_t")
        .whitelist_type("setup_menu_s")
        .whitelist_type("ss_types")
        .whitelist_function("strdup")
        .whitelist_function("strlen")
        .whitelist_function("M_LookupDefault")
        .whitelist_function("dsda_InputSetSpecific")
        .whitelist_function("I_FindFile")
        .whitelist_var("prboom_dir")
        .whitelist_var("numdefaults")
        .whitelist_var("defaults")
        .whitelist_var("DSDA_INPUT_PROFILE_COUNT")
        .whitelist_var("wad_files")
        .whitelist_var("WAD_DATA")
        .generate()
        .expect("Unable to generate bindings");

    let out_path = PathBuf::from(env::var("OUT_DIR").unwrap());
    bindings
        .write_to_file(out_path.join("bindings.rs"))
        .expect("Couldn't write bindings");
}
