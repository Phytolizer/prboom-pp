use cxx::let_cxx_string;
use once_cell::sync::Lazy;
use parking_lot::Mutex;

static GAME_STARTED: Lazy<Mutex<bool>> = Lazy::new(|| Mutex::new(false));

#[cxx::bridge]
mod ffi {
    #[namespace = "rust::cheater"]
    extern "Rust" {
        fn start_game() -> Vec<Cheats>;
    }

    extern "C++" {
        include!("cheater/../m_cheat.hh");
        include!("cheater/../m_argv.hh");

        unsafe fn M_CheckParm(parm: &CxxString) -> i32;
        unsafe fn cheat_god();
    }

    enum Cheats {
        God,
    }
}

fn start_game() -> Vec<ffi::Cheats> {
    if *GAME_STARTED.lock() {
        return vec![];
    }
    *GAME_STARTED.lock() = true;
    if unsafe { check_god_param() } {
        return vec![ffi::Cheats::God];
    }

    vec![]
}

unsafe fn check_god_param() -> bool {
    let_cxx_string!(cheat = "-god");
    if ffi::M_CheckParm(&cheat) != 0 {
        ffi::cheat_god();
        return true;
    }

    false
}
