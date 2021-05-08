#![deny(improper_ctypes)]
#![deny(improper_ctypes_definitions)]

use std::collections::HashMap;
use std::ffi::CString;
use std::fs;
use std::mem::forget;
use std::os::raw::c_char;
use std::os::raw::c_int;
use std::os::raw::c_ulong;
use std::path::PathBuf;
use std::ptr;

use once_cell::sync::Lazy;
use parking_lot::Mutex;
use serde::Deserialize;
use serde::Serialize;

use crate::c::*;

#[repr(C)]
pub struct EnemyStats {
    enemy: mobjtype_t::Type,
    kills: c_ulong,
}

#[repr(C)]
pub struct RawWeaponStats {
    kills: c_ulong,
    enemies: *mut EnemyStats,
    num_enemies: c_ulong,
}

impl Default for RawWeaponStats {
    fn default() -> Self {
        Self {
            kills: 0,
            enemies: ptr::null_mut(),
            num_enemies: 0,
        }
    }
}

#[derive(Debug, Serialize, Deserialize)]
struct WeaponStats {
    kills: usize,
    enemies: HashMap<String, usize>,
}

impl Default for WeaponStats {
    fn default() -> Self {
        Self {
            kills: 0,
            enemies: HashMap::new(),
        }
    }
}

#[no_mangle]
pub extern "C" fn weapon_name(weapon: weapontype_t) -> *const c_char {
    match weapon {
        0 => FIST.as_ptr(),
        1 => PISTOL.as_ptr(),
        2 => SHOTGUN.as_ptr(),
        3 => CHAINGUN.as_ptr(),
        4 => ROCKET_LAUNCHER.as_ptr(),
        5 => PLASMA_RIFLE.as_ptr(),
        6 => BFG_9000.as_ptr(),
        7 => CHAINSAW.as_ptr(),
        8 => SUPER_SHOTGUN.as_ptr(),
        _ => unreachable!(),
    }
}

static FIST: Lazy<CString> =
    Lazy::new(|| CString::new(rust_weapon_name(weapontype_t_wp_fist)).unwrap());
static PISTOL: Lazy<CString> =
    Lazy::new(|| CString::new(rust_weapon_name(weapontype_t_wp_pistol)).unwrap());
static SHOTGUN: Lazy<CString> =
    Lazy::new(|| CString::new(rust_weapon_name(weapontype_t_wp_shotgun)).unwrap());
static CHAINGUN: Lazy<CString> =
    Lazy::new(|| CString::new(rust_weapon_name(weapontype_t_wp_chaingun)).unwrap());
static ROCKET_LAUNCHER: Lazy<CString> =
    Lazy::new(|| CString::new(rust_weapon_name(weapontype_t_wp_missile)).unwrap());
static PLASMA_RIFLE: Lazy<CString> =
    Lazy::new(|| CString::new(rust_weapon_name(weapontype_t_wp_plasma)).unwrap());
static BFG_9000: Lazy<CString> =
    Lazy::new(|| CString::new(rust_weapon_name(weapontype_t_wp_bfg)).unwrap());
static CHAINSAW: Lazy<CString> =
    Lazy::new(|| CString::new(rust_weapon_name(weapontype_t_wp_chainsaw)).unwrap());
static SUPER_SHOTGUN: Lazy<CString> =
    Lazy::new(|| CString::new(rust_weapon_name(weapontype_t_wp_supershotgun)).unwrap());

const fn rust_weapon_name(weapon: weapontype_t) -> &'static str {
    match weapon {
        0 => "fist",
        1 => "pistol",
        2 => "shotgun",
        3 => "chaingun",
        4 => "rocket launcher",
        5 => "plasma rifle",
        6 => "BFG 9000",
        7 => "chainsaw",
        8 => "super shotgun",
        _ => "(invalid weapon)",
    }
}

const fn rust_monster_name(monster: mobjtype_t::Type) -> &'static str {
    match monster {
        mobjtype_t::MT_PLAYER => "player",
        mobjtype_t::MT_POSSESSED => "zombieman",
        mobjtype_t::MT_SHOTGUY => "shotgunner",
        mobjtype_t::MT_VILE => "archvile",
        mobjtype_t::MT_FIRE => "fire",
        mobjtype_t::MT_UNDEAD => "revenant",
        mobjtype_t::MT_TRACER => "revenant's tracer",
        mobjtype_t::MT_SMOKE => "smoke",
        mobjtype_t::MT_FATSO => "mancubus",
        mobjtype_t::MT_FATSHOT => "mancubus' fireball",
        mobjtype_t::MT_CHAINGUY => "chaingunner",
        mobjtype_t::MT_TROOP => "imp",
        mobjtype_t::MT_SERGEANT => "pinky",
        mobjtype_t::MT_SHADOWS => "spectre",
        mobjtype_t::MT_HEAD => "cacodemon",
        mobjtype_t::MT_BRUISER => "baron of hell",
        mobjtype_t::MT_BARON_SHOT => "baron of hell's shot",
        mobjtype_t::MT_KNIGHT => "hell knight",
        mobjtype_t::MT_SKULL => "lost soul",
        mobjtype_t::MT_SPIDER => "spider mastermind",
        mobjtype_t::MT_BABY => "arachnotron",
        mobjtype_t::MT_CYBORG => "cyberdemon",
        mobjtype_t::MT_PAIN => "pain elemental",
        mobjtype_t::MT_WOLFSS => "nazi",
        mobjtype_t::MT_KEEN => "commander keen",
        mobjtype_t::MT_BOSSBRAIN => "icon of sin",
        mobjtype_t::MT_BOSSSPIT => "monster cube",
        mobjtype_t::MT_BOSSTARGET => "icon of sin target",
        mobjtype_t::MT_SPAWNSHOT => "spawn shot (?)",
        mobjtype_t::MT_BARREL => "explosive barrel",
        mobjtype_t::MT_TROOPSHOT => "imp's fireball",
        mobjtype_t::MT_HEADSHOT => "cacodemon's fireball",
        mobjtype_t::MT_ROCKET => "rocket",
        mobjtype_t::MT_PLASMA => "plasma shot",
        mobjtype_t::MT_BFG => "bfg shot",
        mobjtype_t::MT_ARACHPLAZ => "arachnotron's plasma",
        mobjtype_t::MT_PUFF => "bullet puff",
        mobjtype_t::MT_BLOOD => "blood",
        mobjtype_t::MT_TFOG => "teleport fog",
        mobjtype_t::MT_IFOG => "i fog (?)",
        mobjtype_t::MT_TELEPORTMAN => "teleport man (?)",
        mobjtype_t::MT_EXTRABFG => "old bfg shot",
        _ => "(unknown monster)",
    }
}

static KILL_STATS: Lazy<Mutex<HashMap<String, WeaponStats>>> = Lazy::new(|| {
    let mut map = HashMap::new();
    map.insert(
        rust_weapon_name(weapontype_t_wp_fist).to_string(),
        WeaponStats::default(),
    );
    map.insert(
        rust_weapon_name(weapontype_t_wp_pistol).to_string(),
        WeaponStats::default(),
    );
    map.insert(
        rust_weapon_name(weapontype_t_wp_shotgun).to_string(),
        WeaponStats::default(),
    );
    map.insert(
        rust_weapon_name(weapontype_t_wp_chaingun).to_string(),
        WeaponStats::default(),
    );
    map.insert(
        rust_weapon_name(weapontype_t_wp_missile).to_string(),
        WeaponStats::default(),
    );
    map.insert(
        rust_weapon_name(weapontype_t_wp_plasma).to_string(),
        WeaponStats::default(),
    );
    map.insert(
        rust_weapon_name(weapontype_t_wp_bfg).to_string(),
        WeaponStats::default(),
    );
    map.insert(
        rust_weapon_name(weapontype_t_wp_chainsaw).to_string(),
        WeaponStats::default(),
    );
    map.insert(
        rust_weapon_name(weapontype_t_wp_supershotgun).to_string(),
        WeaponStats::default(),
    );

    Mutex::new(map)
});

unsafe fn get_weapon_stats_filename() -> PathBuf {
    let prbdir_len = strlen(prboom_dir.as_ptr()) as usize;
    dirs::home_dir()
        .unwrap()
        .join({
            &std::str::from_utf8(std::slice::from_raw_parts(
                prboom_dir.as_ptr() as *const u8,
                prbdir_len,
            ))
            .unwrap()[1..]
        })
        .join("weapon_stats.ron")
}

/// # Safety
/// This function just needs the prboom_dir value as a String.
/// It's probably fine, as that is a constant.
#[no_mangle]
pub unsafe extern "C" fn load_weapon_stats() -> c_int {
    let contents = match fs::read(get_weapon_stats_filename()) {
        Ok(c) => c,
        Err(e) => {
            eprintln!("Couldn't read weapon stats: {}", e);
            return 1;
        }
    };

    *KILL_STATS.lock() = match ron::de::from_bytes(&contents) {
        Ok(ks) => ks,
        Err(e) => {
            eprintln!("Couldn't parse weapon stats: {}", e);
            return 2;
        }
    };

    0
}

/// # Safety
/// This function just needs to get the prboom_dir value as a String. It's probably fine.
#[no_mangle]
pub unsafe extern "C" fn save_weapon_stats() -> c_int {
    let contents =
        ron::ser::to_string_pretty(&*(KILL_STATS.lock()), ron::ser::PrettyConfig::default())
            .unwrap();

    if let Err(e) = fs::write(get_weapon_stats_filename(), contents) {
        eprintln!(
            "Couldn't write to {}: {}",
            get_weapon_stats_filename().to_string_lossy(),
            e
        );
        return 2;
    }

    0
}

#[no_mangle]
pub extern "C" fn add_kill(weapon: weapontype_t, enemy: mobjtype_t::Type) {
    let mut kill_stats = KILL_STATS.lock();
    let stats = kill_stats.get_mut(rust_weapon_name(weapon)).unwrap();
    stats.kills += 1;
    let enemy_stats = stats.enemies.entry(format!("{}", enemy));
    enemy_stats.and_modify(|v| *v += 1).or_insert(1);
}

/// # Safety
/// This function can only take Rust-allocated stats.
/// It deallocates them using drop, so be very careful on the C/C++ end.
#[no_mangle]
pub unsafe extern "C" fn cleanup_stats(stats: *mut RawWeaponStats) {
    drop(Vec::from_raw_parts(
        (*stats).enemies,
        (*stats).num_enemies as usize,
        (*stats).num_enemies as usize,
    ));
    (*stats).num_enemies = 0;
    (*stats).kills = 0;
    (*stats).enemies = ptr::null_mut();
}

/// # Safety
/// This function allocates a RawWeaponStats and passes it by pointer.
/// It is safe as long as the C/C++ side remembers to call cleanup_stats.
#[no_mangle]
pub unsafe extern "C" fn get_stats(weapon: weapontype_t, raw_stats: *mut RawWeaponStats) -> c_int {
    let kill_stats = KILL_STATS.lock();
    let stats = match kill_stats.get(rust_weapon_name(weapon)) {
        Some(w) => w,
        None => return 1,
    };
    let mut enemy_stats = stats
        .enemies
        .iter()
        .map(|(enemy, &kills)| EnemyStats {
            enemy: enemy.parse().unwrap(),
            kills: kills as c_ulong,
        })
        .collect::<Vec<_>>();

    enemy_stats.sort_by_key(|stats| stats.kills);
    let enemies = enemy_stats.as_mut_ptr();
    let num_enemies = enemy_stats.len() as c_ulong;
    forget(enemy_stats);
    *raw_stats = RawWeaponStats {
        kills: stats.kills as c_ulong,
        enemies,
        num_enemies,
    };
    0
}
