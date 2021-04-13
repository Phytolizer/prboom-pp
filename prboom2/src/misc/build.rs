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
        .allowlist_type("default_t")
        .allowlist_type("sfxenum_t")
        .allowlist_type("weapontype_t")
        .allowlist_type("mobjtype_t")
        .allowlist_type("setup_menu_s")
        .allowlist_type("ss_types")
        .allowlist_type("dsda_input_t")
        .allowlist_function("strdup")
        .allowlist_function("strlen")
        .allowlist_function("M_LookupDefault")
        .allowlist_function("dsda_InputSetSpecific")
        .allowlist_function("I_FindFile")
        .allowlist_function("dsda_InputResetSpecific")
        .allowlist_function("dsda_InputAddSpecificMouseB")
        .allowlist_function("dsda_InputAddSpecificJoyB")
        .allowlist_function("dsda_InputAddSpecificKey")
        .allowlist_var("prboom_dir")
        .allowlist_var("numdefaults")
        .allowlist_var("defaults")
        .allowlist_var("DSDA_INPUT_PROFILE_COUNT")
        .allowlist_var("wad_files")
        .allowlist_var("WAD_DATA")
        .allowlist_var("dsda_input")
        .generate()
        .expect("Unable to generate bindings");

    let out_path = PathBuf::from(env::var("OUT_DIR").unwrap());
    bindings
        .write_to_file(out_path.join("bindings.rs"))
        .expect("Couldn't write bindings");
}
