use cxx::let_cxx_string;

#[cxx::bridge]
mod ffi {

    extern "Rust" {
        unsafe fn apply_cheats() -> bool;
    }

    extern "C++" {
        include!("../m_cheat.hh");
        include!("../m_argv.hh");

        unsafe fn M_CheckParm(parm: &CxxString) -> i32;
        unsafe fn cheat_god();
    }
}

unsafe fn apply_cheats() -> bool {
    let_cxx_string!(cheat = "-god");
    if ffi::M_CheckParm(&cheat) != 0 {
        ffi::cheat_god();
        return true;
    }

    false
}
