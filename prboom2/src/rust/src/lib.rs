#![allow(non_upper_case_globals)]
#![allow(non_camel_case_types)]
#![allow(non_snake_case)]
#![deny(unused_unsafe)]
#![deny(unused_variables)]
#![deny(unused_mut)]
#![deny(unused_qualifications)]
#![deny(unused_lifetimes)]
#![deny(unused_imports)]
#![deny(unused_crate_dependencies)]
#![deny(unused_allocation)]

use std::collections::HashMap;
use std::ffi::CString;
use std::os::raw::c_char;
use std::os::raw::c_int;
use std::os::raw::c_ulong;
use std::process::exit;

use nom::branch::alt;
use nom::bytes::complete::take_till1;
use nom::bytes::complete::take_while1;
use nom::bytes::complete::{tag, take_while};
use nom::character::complete::char;
use nom::character::complete::one_of;
use nom::combinator::all_consuming;
use nom::combinator::{map, opt};
use nom::multi::{many0, many1};
use nom::sequence::{pair, preceded, terminated, tuple};
use nom::{combinator, IResult};

// use pom::parser::is_a;
// use pom::parser::one_of;
// use pom::parser::Parser;
// use pom::parser::sym;
// use pom::parser::tag;
//
mod c;
mod stats;
pub use stats::*;

#[repr(C)]
#[derive(Clone, Copy)]
pub struct Key {
    cls: *mut c_char,
    cls_len: usize,
    name: *mut c_char,
    name_len: usize,
}

impl From<RustKey> for Key {
    fn from(mut k: RustKey) -> Self {
        let cls = k.class.as_mut_ptr() as *mut c_char;
        let cls_len = k.class.len();
        std::mem::forget(k.class);
        let name = k.name.as_mut_ptr() as *mut c_char;
        let name_len = k.name.len();
        std::mem::forget(k.name);
        Self {
            cls,
            cls_len,
            name,
            name_len,
        }
    }
}

#[derive(Debug, Clone, PartialEq, Eq, Hash)]
struct RustKey {
    class: String,
    name: String,
}

impl From<(String, String)> for RustKey {
    fn from((c, n): (String, String)) -> Self {
        Self { class: c, name: n }
    }
}

impl ToString for RustKey {
    fn to_string(&self) -> String {
        self.class.clone() + "/" + &self.name
    }
}

pub struct SndInfo(Vec<Statement>);

#[repr(C)]
#[derive(Clone, Copy)]
pub struct SoundInfo {
    sfx: c::sfxenum_t,
    lumps: *const *const u8,
    lump_lens: *const usize,
    num_lumps: usize,
    singularity: bool,
    pitch: c_int,
    volume: c_int,
}

#[derive(Clone)]
struct RustSoundInfo {
    names: Vec<String>,
    refs: Vec<RustKey>,
    singularity: bool,
    pitch: c_int,
    volume: c_int,
}

impl RustSoundInfo {
    fn from_pitch(pitch: c_int) -> Self {
        Self {
            pitch,
            ..Default::default()
        }
    }

    fn from_volume(vol: c_int) -> Self {
        Self {
            volume: vol,
            ..Default::default()
        }
    }

    fn new_singular() -> Self {
        Self {
            singularity: true,
            ..Default::default()
        }
    }
}

impl From<String> for RustSoundInfo {
    fn from(s: String) -> Self {
        Self {
            names: vec![s],
            ..Default::default()
        }
    }
}

impl From<Vec<RustKey>> for RustSoundInfo {
    fn from(refs: Vec<RustKey>) -> Self {
        Self {
            refs,
            ..Default::default()
        }
    }
}

impl Default for RustSoundInfo {
    fn default() -> Self {
        Self {
            names: vec![],
            refs: vec![],
            singularity: false,
            pitch: -1,
            volume: -1,
        }
    }
}

#[no_mangle]
/// # Safety
/// This function cleans up after the C++ side is finished with the data
/// that was passed py pointer from parse_sndinfo.
pub unsafe extern "C" fn deallocate_rust_sound_info(ptr: *mut SoundInfo, len: c_ulong) {
    drop(Vec::from_raw_parts(ptr, len as usize, len as usize));
}

fn sfx_for_sound(snd: &RustKey) -> Option<c::sfxenum_t> {
    match snd.class.as_str() {
        "weapons" => match snd.name.as_str() {
            s if s.starts_with("sshotl") => Some(c::sfxenum_t_sfx_dbload),
            s if s == "chngun" || s.starts_with("chngn") => Some(c::sfxenum_t_sfx_player_chaingun),
            "rocklx" => Some(c::sfxenum_t_sfx_rocket_explode),
            "plasmax" => Some(c::sfxenum_t_sfx_plasma_sizzle),
            _ => None,
        },
        "dog" => match snd.name.as_str() {
            s if s.starts_with("active") => Some(c::sfxenum_t_sfx_dgact),
            "attack" => Some(c::sfxenum_t_sfx_dgatk),
            s if s.starts_with("death") => Some(c::sfxenum_t_sfx_dgdth),
            "pain" => Some(c::sfxenum_t_sfx_dgpain),
            "sight" => Some(c::sfxenum_t_sfx_dgsit),
            _ => None,
        },
        "vile" => match snd.name.as_str() {
            "raise" => Some(c::sfxenum_t_sfx_archvile_resurrect),
            "stop" => Some(c::sfxenum_t_sfx_archvile_zap),
            _ => None,
        },
        "skeleton" => match snd.name.as_str() {
            "pain" => Some(c::sfxenum_t_sfx_revenant_pain),
            s if s.starts_with("melee") => Some(c::sfxenum_t_sfx_revenant_punch),
            s if s.starts_with("tracex") => Some(c::sfxenum_t_sfx_tracer_explode),
            _ => None,
        },
        "fatso" => match snd.name.as_str() {
            "active" => Some(c::sfxenum_t_sfx_mancubus_active),
            "attack" => Some(c::sfxenum_t_sfx_mancubus_shoot),
            "shotx" => Some(c::sfxenum_t_sfx_mancubus_projectile_explode),
            _ => None,
        },
        "chainguy" => match snd.name.as_str() {
            s if s.starts_with("sight") => Some(c::sfxenum_t_sfx_chaingunner_wake),
            s if s.starts_with("active") => Some(c::sfxenum_t_sfx_chaingunner_active),
            "pain" => Some(c::sfxenum_t_sfx_chaingunner_pain),
            s if s.starts_with("death") => Some(c::sfxenum_t_sfx_chaingunner_death),
            "attack" => Some(c::sfxenum_t_sfx_chaingunner_shoot),
            _ => None,
        },
        "imp" => match snd.name.as_str() {
            "pain" => Some(c::sfxenum_t_sfx_imp_pain),
            "attack" => Some(c::sfxenum_t_sfx_imp_shoot),
            s if s.starts_with("shotx") => Some(c::sfxenum_t_sfx_imp_fireball_explode),
            _ => None,
        },
        "demon" => match snd.name.as_str() {
            s if s.starts_with("active") => Some(c::sfxenum_t_sfx_pinky_active),
            _ => None,
        },
        "spectre" => match snd.name.as_str() {
            s if s.starts_with("active") => Some(c::sfxenum_t_sfx_spectre_active),
            _ => None,
        },
        "caco" => match snd.name.as_str() {
            "active" => Some(c::sfxenum_t_sfx_cacodemon_active),
            "pain" => Some(c::sfxenum_t_sfx_cacodemon_pain),
            "attack" => Some(c::sfxenum_t_sfx_cacodemon_shoot),
            s if s.starts_with("shotx") => Some(c::sfxenum_t_sfx_cacodemon_projectile_explode),
            _ => None,
        },
        "baron" => match snd.name.as_str() {
            s if s.starts_with("active") => Some(c::sfxenum_t_sfx_baron_active),
            "attack" => Some(c::sfxenum_t_sfx_baron_shoot),
            "shotx" => Some(c::sfxenum_t_sfx_baron_shot_sizzle),
            _ => None,
        },
        "knight" => match snd.name.as_str() {
            "active" => Some(c::sfxenum_t_sfx_hellknight_active),
            "pain" => Some(c::sfxenum_t_sfx_hellknight_pain),
            _ => None,
        },
        "skull" => match snd.name.as_str() {
            "active" => Some(c::sfxenum_t_sfx_lostsoul_active),
            "pain" => Some(c::sfxenum_t_sfx_lostsoul_pain),
            "death" => Some(c::sfxenum_t_sfx_lostsoul_death),
            _ => None,
        },
        "spider" => match snd.name.as_str() {
            "active" => Some(c::sfxenum_t_sfx_spidermastermind_active),
            "pain" => Some(c::sfxenum_t_sfx_spidermastermind_pain),
            "attack" => Some(c::sfxenum_t_sfx_spidermastermind_shoot),
            s if s.starts_with("walk") => Some(c::sfxenum_t_sfx_metal),
            _ => None,
        },
        "baby" => match snd.name.as_str() {
            "pain" => Some(c::sfxenum_t_sfx_arachnotron_pain),
            "attack" => Some(c::sfxenum_t_sfx_arachnotron_shoot),
            "shotx" => Some(c::sfxenum_t_sfx_arachnotron_plasma_sizzle),
            _ => None,
        },
        "cyber" => match snd.name.as_str() {
            s if s.starts_with("active") => Some(c::sfxenum_t_sfx_cyberdemon_active),
            s if s.starts_with("hoof") => Some(c::sfxenum_t_sfx_hoof),
            _ => None,
        },
        "wolfss" => match snd.name.as_str() {
            "attack" => Some(c::sfxenum_t_sfx_ss_shoot),
            _ => None,
        },
        "world" => match snd.name.as_str() {
            s if s.starts_with("barrel") || s == "barrelx" => Some(c::sfxenum_t_sfx_barexp),
            "drip" => Some(c::sfxenum_t_sfx_ignored),
            "watersplash" => Some(c::sfxenum_t_sfx_ignored),
            _ => None,
        },
        _ => None,
    }
}

#[no_mangle]
/// # Safety
/// This function uses a ptr/length pair to construct a slice.
/// It is a safe conversion as long as W_LumpLength and W_CacheLumpNum return accurate values.
pub unsafe extern "C" fn parse_sndinfo(
    heretic: bool,
    strict: bool,
    lump: *const c_char,
    lump_length: c_int,
    buf: *mut *mut SoundInfo,
    buf_len: *mut c_ulong,
) {
    let lump = std::slice::from_raw_parts(lump, lump_length as usize);

    let mut lump_str = String::new();
    for c in lump {
        let c = *c as u8 as char;
        lump_str.push(c);
    }

    let sndinfo = do_parse_sndinfo(lump_str);
    let mut stmts = sndinfo.0;
    let mut evaluated = vec![];
    let mut lumps = HashMap::<RustKey, RustSoundInfo>::new();
    let mut aliases = HashMap::<RustKey, RustKey>::new();
    while let Some(stmt) = stmts.pop() {
        match stmt {
            Statement::Sound(snd, name) => {
                if let Some(lmp) = lumps.get_mut(&snd) {
                    lmp.names.push(name.0);
                } else {
                    lumps.insert(snd, RustSoundInfo::from(name.0));
                }
            }
            Statement::Alias(a, r) => {
                aliases.insert(r, a);
            }
            Statement::If(IfStatement {
                kind,
                stmts: mut then,
            }) => {
                if heretic && kind == IfStatementKind::Heretic
                    || !heretic && kind == IfStatementKind::Doom
                {
                    stmts.append(&mut then);
                }
            }
            // Statement::MusicAlias(_, _) => {}
            Statement::PitchSet(snd, pch) => {
                if let Some(lmp) = lumps.get_mut(&snd) {
                    lmp.pitch = pch;
                } else {
                    lumps.insert(snd, RustSoundInfo::from_pitch(pch));
                }
            }
            Statement::Random(snd, mut lmps) => {
                if let Some(lmp) = lumps.get_mut(&snd) {
                    lmp.refs.append(&mut lmps);
                } else {
                    lumps.insert(snd, lmps.into());
                }
            }
            Statement::Singular(snd) => {
                if let Some(lmp) = lumps.get_mut(&snd) {
                    lmp.singularity = true;
                } else {
                    lumps.insert(snd, RustSoundInfo::new_singular());
                }
            }
            Statement::Volume(snd, vol) => {
                if let Some(lmp) = lumps.get_mut(&snd) {
                    lmp.volume = vol;
                } else {
                    lumps.insert(snd, RustSoundInfo::from_volume(vol));
                }
            }
            Statement::Ignored => {}
        }
    }

    let mut refs = HashMap::<RustKey, Vec<String>>::new();

    for (snd, lmp) in lumps.iter() {
        if let Some(r) = refs.get_mut(snd) {
            r.append(&mut lmp.names.clone());
        } else {
            refs.insert(snd.clone(), lmp.names.clone());
        }

        if let Some(a) = aliases.get(snd) {
            refs.insert(a.clone(), lmp.names.clone());
        }
    }

    for snd in lumps.keys() {
        if let Some(r) = refs.get(snd).cloned() {
            let num_strs = r.len();
            let lump_lens = r.iter().map(String::len).collect::<Vec<_>>();
            let str_ptrs = r
                .into_iter()
                .map(|s| {
                    let s = CString::new(s.as_bytes()).unwrap();
                    let p = s.as_bytes_with_nul().as_ptr();
                    std::mem::forget(s);
                    p
                })
                .collect::<Vec<_>>();
            let strs = str_ptrs.as_ptr();
            std::mem::forget(str_ptrs);
            let lens = lump_lens.as_ptr();
            std::mem::forget(lump_lens);
            if let Some(sfx) = sfx_for_sound(snd) {
                evaluated.push(SoundInfo {
                    sfx,
                    lumps: strs,
                    lump_lens: lens,
                    num_lumps: num_strs,
                    singularity: lumps[snd].singularity,
                    pitch: lumps[snd].pitch,
                    volume: lumps[snd].volume,
                });
            } else {
                eprintln!(
                    "sndinfo::parse: warning: unrecognized sound key {}",
                    snd.to_string()
                );
                if strict {
                    exit(1);
                }
            }
        } else {
            eprintln!(
                "sndinfo::parse: no definition for sound {}",
                snd.to_string()
            );
        }
    }

    let ptr = evaluated.as_mut_ptr();
    let len = evaluated.len();
    std::mem::forget(evaluated);
    *buf = ptr;
    *buf_len = len as c_ulong;
}

#[derive(Debug, Clone, PartialEq, Eq)]
struct Lump(String);

#[derive(Debug, Clone, PartialEq, Eq)]
enum IfStatementKind {
    Doom,
    Heretic,
}

#[derive(Debug, Clone, PartialEq, Eq)]
struct IfStatement {
    kind: IfStatementKind,
    stmts: Vec<Statement>,
}

#[derive(Debug, Clone, PartialEq, Eq)]
enum Statement {
    Sound(RustKey, Lump),
    Alias(RustKey, RustKey),
    If(IfStatement),
    // MusicAlias(String, String),
    PitchSet(RustKey, c_int),
    Random(RustKey, Vec<RustKey>),
    Singular(RustKey),
    Volume(RustKey, c_int),
    Ignored,
}

fn whitespace(text: &str) -> IResult<&str, ()> {
    map(
        take_while1(|c: char| c.is_ascii_whitespace() && c != '\n'),
        |_| (),
    )(text)
}

fn any_whitespace(text: &str) -> IResult<&str, ()> {
    map(take_while(|c: char| c.is_ascii_whitespace()), |_| ())(text)
}

fn integer(text: &str) -> IResult<&str, i32> {
    combinator::map_res(take_while1(|c: char| c.is_ascii_digit()), str::parse)(text)
}

fn ident(text: &str) -> IResult<&str, &str> {
    take_while1(|c: char| c.is_ascii_alphanumeric())(text)
}

fn sound(text: &str) -> IResult<&str, RustKey> {
    map(tuple((ident, char('/'), ident)), |(c, _, n)| {
        (c.to_owned(), n.to_owned()).into()
    })(text)
}

fn comment(text: &str) -> IResult<&str, Statement> {
    map(preceded(tag("//"), take_while(|c: char| c != '\n')), |_| {
        Statement::Ignored
    })(text)
}

fn lump(text: &str) -> IResult<&str, Lump> {
    map(
        preceded(
            tuple((char('d'), one_of("sp"))),
            take_while1(|c: char| c.is_ascii_alphanumeric()),
        ),
        |c: &str| Lump(c.to_string()),
    )(text)
}

fn sound_stmt(text: &str) -> IResult<&str, Statement> {
    map(tuple((sound, preceded(whitespace, lump))), |(s, l)| {
        Statement::Sound(s, l)
    })(text)
}

fn singular(text: &str) -> IResult<&str, Statement> {
    map(preceded(tag("$singular"), sound), |snd| {
        Statement::Singular(snd)
    })(text)
}

fn alias(text: &str) -> IResult<&str, Statement> {
    map(
        tuple((
            preceded(pair(tag("$alias"), whitespace), sound),
            preceded(whitespace, sound),
        )),
        |(n, v)| Statement::Alias(n, v),
    )(text)
}

fn ignored(text: &str) -> IResult<&str, Statement> {
    map(
        alt((
            tag("$ambient"),
            tag("$archivepath"),
            tag("$attenuation"),
            tag("$edfoverride"),
            tag("$limit"),
            tag("$map"),
            tag("$mididevice"),
            tag("$musicalias"),
            tag("$musicvolume"),
            tag("$pitchshift"),
            tag("$pitchshiftrange"),
            tag("$playeralias"),
            tag("$playercompat"),
            tag("$playersound"),
            tag("$playersounddup"),
            tag("$registered"),
            tag("$rolloff"),
        )),
        |_| Statement::Ignored,
    )(text)
}

fn non_if_stmt(text: &str) -> IResult<&str, Statement> {
    alt((
        alias, pitch, ignored, sound_stmt, random, volume, singular, comment,
    ))(text)
}

fn if_stmt(text: &str) -> IResult<&str, Statement> {
    fn rest(text: &str) -> IResult<&str, Vec<Statement>> {
        terminated(many0(preceded(any_whitespace, non_if_stmt)), any_whitespace)(text)
    }

    alt((
        map(preceded(tag("$ifdoom"), rest), |stmts| {
            Statement::If(IfStatement {
                kind: IfStatementKind::Doom,
                stmts,
            })
        }),
        map(preceded(tag("$ifheretic"), rest), |stmts| {
            Statement::If(IfStatement {
                kind: IfStatementKind::Heretic,
                stmts,
            })
        }),
        map(
            preceded(alt((tag("$ifhexen"), tag("$ifstrife"))), rest),
            |_| Statement::Ignored,
        ),
    ))(text)
}

fn pitch(text: &str) -> IResult<&str, Statement> {
    map(
        preceded(tag("$pitchset"), tuple((sound, integer))),
        |(s, p)| Statement::PitchSet(s, p),
    )(text)
}

fn random(text: &str) -> IResult<&str, Statement> {
    map(
        tuple((
            preceded(tuple((tag("$random"), whitespace)), sound),
            whitespace,
            char('{'),
            terminated(
                many1(preceded(whitespace, sound)),
                tuple((opt(whitespace), char('}'), any_whitespace)),
            ),
        )),
        |(s, _, _, ss)| Statement::Random(s, ss),
    )(text)
}

fn volume(text: &str) -> IResult<&str, Statement> {
    map(
        tuple((
            preceded(tuple((tag("$volume"), whitespace)), sound),
            preceded(whitespace, integer),
        )),
        |(s, v)| Statement::Volume(s, v),
    )(text)
}

fn bad_stmt(text: &str) -> IResult<&str, Statement> {
    map(take_till1(|c| c == '\n'), |_| Statement::Ignored)(text)
}

fn sndinfo_parser(text: &str) -> IResult<&str, Vec<Statement>> {
    all_consuming(many0(terminated(
        alt((non_if_stmt, if_stmt, bad_stmt)),
        opt(any_whitespace),
    )))(text)
}

fn do_parse_sndinfo(text: String) -> SndInfo {
    let text = text.replace("\r", "");
    dbg!(sndinfo_parser(&text))
        .ok()
        .map(|(_, info)| SndInfo(info))
        .unwrap()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn please_work() {
        assert_eq!(
            sound_stmt("misc/icebreak icebrk1a"),
            Ok((
                "",
                Statement::Sound(
                    RustKey {
                        class: "misc".to_string(),
                        name: "icebreak".to_string()
                    },
                    Lump("icebrk1a".to_string())
                )
            ))
        );
    }
}
