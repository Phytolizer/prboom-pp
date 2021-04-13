use cheater_macros::check_cheat_param;
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

    unsafe extern "C++" {
        include!("m_cheat.hh");
        include!("m_argv.hh");

        fn M_CheckParm(parm: &CxxString) -> i32;
        fn cheat_god();
        fn cheat_buddha();
    }

    enum Cheats {
        IDMUS,
        IDCHOPPERS,
        IDDQD,
        IDKFA,
        IDFA,
        IDSPISPOPD,
        IDCLIP,
        IDBEHOLDH,
        IDBEHOLDM,
        IDBEHOLDV,
        IDBEHOLDS,
        IDBEHOLDI,
        IDBEHOLDR,
        IDBEHOLDA,
        IDBEHOLDL,
        IDBEHOLD,
        IDCLEV,
        IDMYPOS,
        IDRATE,
        TNTCOMP,
        TNTEM,
        IDDT,
        TNTHOM,
        TNTKEY,
        TNTKEYR,
        TNTKEYY,
        TNTKEYB,
        TNTKEYRC,
        TNTKEYYC,
        TNTKEYBC,
        TNTKEYRS,
        TNTKEYYS,
        TNTKEYBS,
        TNTKA,
        TNTWEAP,
        TNTWEAPX,
        TNTAMMO,
        TNTAMMOX,
        TNTTRAN,
        TNTSMART,
        TNTPITCH,
        TNTRAN,
        TNTAMO,
        TNTAMOX,
        TNTFAST,
        TNTICE,
        TNTPUSH,
        NOTARGET,
        FLY,
        BUDDHA,
    }
}

fn start_game() -> Vec<ffi::Cheats> {
    if *GAME_STARTED.lock() {
        return vec![];
    }
    *GAME_STARTED.lock() = true;
    let mut cheats = vec![];
    if unsafe { check_god_cheat() } {
        cheats.push(ffi::Cheats::IDDQD);
    }
    if unsafe { check_buddha_cheat() } {
        cheats.push(ffi::Cheats::BUDDHA);
    }

    vec![]
}

check_cheat_param!("god" => cheat_god);
check_cheat_param!("buddha" => cheat_buddha);
