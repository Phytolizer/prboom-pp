#![deny(improper_ctypes)]
#![deny(improper_ctypes_definitions)]

use std::collections::HashMap;
use std::fs;
use std::mem::forget;
use std::mem::size_of;
use std::mem::size_of_val;
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
    enemy: mobjtype_t,
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
    enemies: HashMap<mobjtype_t, usize>,
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
        0 => b"fist\0" as *const u8 as *const i8,
        1 => b"pistol\0" as *const u8 as *const i8,
        2 => b"shotgun\0" as *const u8 as *const i8,
        3 => b"chaingun\0" as *const u8 as *const i8,
        4 => b"rocket launcher\0" as *const u8 as *const i8,
        5 => b"plasma rifle\0" as *const u8 as *const i8,
        6 => b"BFG 9000\0" as *const u8 as *const i8,
        7 => b"chainsaw\0" as *const u8 as *const i8,
        8 => b"super shotgun\0" as *const u8 as *const i8,
        _ => b"(invalid weapon)\0" as *const u8 as *const i8,
    }
}

static KILL_STATS: Lazy<Mutex<HashMap<weapontype_t, WeaponStats>>> = Lazy::new(|| {
    let mut map = HashMap::new();
    map.insert(weapontype_t_wp_fist, WeaponStats::default());
    map.insert(weapontype_t_wp_pistol, WeaponStats::default());
    map.insert(weapontype_t_wp_shotgun, WeaponStats::default());
    map.insert(weapontype_t_wp_chaingun, WeaponStats::default());
    map.insert(weapontype_t_wp_missile, WeaponStats::default());
    map.insert(weapontype_t_wp_plasma, WeaponStats::default());
    map.insert(weapontype_t_wp_bfg, WeaponStats::default());
    map.insert(weapontype_t_wp_chainsaw, WeaponStats::default());
    map.insert(weapontype_t_wp_supershotgun, WeaponStats::default());

    Mutex::new(map)
});

unsafe fn get_weapon_stats_filename() -> PathBuf {
    let prbdir_len = size_of_val(&prboom_dir) / size_of::<*const c_char>();
    dirs::home_dir()
        .unwrap()
        .join(String::from_raw_parts(
            prboom_dir.as_mut_ptr() as *mut u8,
            prbdir_len,
            prbdir_len,
        ))
        .join("weapon_stats.toml")
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

    *KILL_STATS.lock() = match toml::from_slice(&contents) {
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
    let contents = match toml::to_string_pretty(&*KILL_STATS.lock()) {
        Ok(c) => c,
        Err(_) => return 1,
    };

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
pub extern "C" fn add_kill(weapon: weapontype_t, enemy: mobjtype_t) {
    let mut kill_stats = KILL_STATS.lock();
    let stats = kill_stats.get_mut(&weapon).unwrap();
    stats.kills += 1;
    let enemy_stats = stats.enemies.entry(enemy);
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
    let stats = match kill_stats.get(&weapon) {
        Some(w) => w,
        None => return 1,
    };
    let mut enemy_stats = stats
        .enemies
        .iter()
        .map(|(&enemy, &kills)| EnemyStats {
            enemy,
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
