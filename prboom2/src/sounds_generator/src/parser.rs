use std::fmt::Display;
use std::os::raw::c_int;

use character::complete::char;
use nom::branch::alt;
use nom::bytes::complete::tag;
use nom::bytes::complete::take_while;
use nom::character;
use nom::character::complete::multispace0;
use nom::character::complete::multispace1;
use nom::character::complete::satisfy;
use nom::combinator::all_consuming;
use nom::combinator::map;
use nom::combinator::map_res;
use nom::combinator::opt;
use nom::dbg_dmp;
use nom::multi::many0;
use nom::multi::many1;
use nom::sequence::delimited;
use nom::sequence::terminated;
use nom::sequence::tuple;
use nom::IResult;

#[derive(Debug)]
pub struct SoundDefinition {
    pub names: Vec<String>,
    pub singular: bool,
    pub priority: c_int,
    pub link: String,
    pub pitch: c_int,
    pub volume: c_int,
    pub data: String,
    pub usefulness: c_int,
    pub lump_nums: Vec<c_int>,
    pub num_channels: c_int,
    pub alt_names: Vec<String>,
}

impl Display for SoundDefinition {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "sfxinfo_t{{")?;
        write!(f, "{{")?;
        for name in &self.names {
            write!(f, "{},", name)?;
        }
        write!(f, "}},")?;
        write!(f, "{},", self.singular)?;
        write!(f, "{},", self.priority)?;
        write!(f, "{},", self.link)?;
        write!(f, "{},", self.pitch)?;
        write!(f, "{},", self.volume)?;
        write!(f, "{},", self.data)?;
        write!(f, "{},", self.usefulness)?;
        write!(f, "{{")?;
        for lump in &self.lump_nums {
            write!(f, "{},", lump)?;
        }
        write!(f, "}},")?;
        write!(f, "{},", self.num_channels)?;
        write!(f, "{{")?;
        for name in &self.alt_names {
            write!(f, "{},", name)?;
        }
        write!(f, "}}")?;

        write!(f, "}},")
    }
}

#[derive(Debug)]
pub struct SoundArray(Vec<SoundDefinition>);

impl IntoIterator for SoundArray {
    type Item = SoundDefinition;

    type IntoIter = std::vec::IntoIter<Self::Item>;

    fn into_iter(self) -> Self::IntoIter {
        self.0.into_iter()
    }
}

pub struct InputSection<'src> {
    pub prefix: &'src str,
    pub sounds: SoundArray,
    pub suffix: &'src str,
}

pub fn parse_input_file(text: &str) -> IResult<&str, Vec<InputSection>> {
    all_consuming(many1(map(
        tuple((
            delimited(
                tag("%%literal"),
                take_while(|c: char| c != '%'),
                tag("%%endliteral"),
            ),
            tuple((
                tag("sfxinfo_t doom_S_sfx[] = {"),
                parse_sound_definitions,
                tag("};"),
            )),
            delimited(
                tag("%%literal"),
                take_while(|c: char| c != '%'),
                tag("%%endliteral"),
            ),
        )),
        |(prefix, (_, sounds, _), suffix)| InputSection {
            prefix,
            sounds,
            suffix,
        },
    )))(text)
}

fn parse_sound_definitions(text: &str) -> IResult<&str, SoundArray> {
    map(many0(terminated(sound_definition, multispace0)), |defs| {
        SoundArray(defs)
    })(text)
}

fn sound_definition(text: &str) -> IResult<&str, SoundDefinition> {
    map(
        tuple((
            multispace0,
            string_vec,
            char(','),
            multispace0,
            boolean,
            char(','),
            multispace0,
            integer,
            char(','),
            multispace0,
            ptr,
            char(','),
            multispace0,
            integer,
            char(','),
            multispace0,
            integer,
            char(','),
            multispace0,
            ptr,
            multispace0,
        )),
        |(
            _,
            names,
            _,
            _,
            singular,
            _,
            _,
            priority,
            _,
            _,
            link,
            _,
            _,
            pitch,
            _,
            _,
            volume,
            _,
            _,
            data,
            _,
        )| {
            SoundDefinition {
                names,
                singular,
                priority,
                link,
                pitch,
                volume,
                data,
                usefulness: 0,
                lump_nums: vec![-1],
                num_channels: 0,
                alt_names: vec![],
            }
        },
    )(text)
}

fn string_literal(text: &str) -> IResult<&str, String> {
    map(
        delimited(char('"'), take_while(|c: char| c != '"'), char('"')),
        str::to_owned,
    )(text)
}

fn string_vec(text: &str) -> IResult<&str, Vec<String>> {
    delimited(char('{'), many0(string_literal), char('}'))(text)
}

fn boolean(text: &str) -> IResult<&str, bool> {
    alt((tag("true"), tag("false")))(text).map(|(rest, text)| (rest, text == "true"))
}

fn integer(text: &str) -> IResult<&str, c_int> {
    map_res(
        tuple((opt(char('-')), take_while(|c: char| c.is_ascii_digit()))),
        |(minus, number): (Option<char>, &str)| {
            if minus.is_some() {
                number.parse().map(|n: c_int| -n)
            } else {
                number.parse()
            }
        },
    )(text)
}

fn ptr(text: &str) -> IResult<&str, String> {
    map(
        alt((
            map(tag("nullptr"), |s: &str| s.to_owned()),
            map(tuple((char('&'), value)), |(amp, val)| {
                format!("{}{}", amp, val)
            }),
        )),
        |val| val.to_owned(),
    )(text)
}

fn value(text: &str) -> IResult<&str, String> {
    map(
        tuple((
            take_while(|c: char| c.is_ascii_alphanumeric()),
            opt(array_index),
        )),
        |(ident, subscript)| format!("{}{}", ident, subscript.unwrap_or(String::new())),
    )(text)
}

fn array_index(text: &str) -> IResult<&str, String> {
    map(tuple((char('['), ident, char(']'))), |(lb, ident, rb)| {
        format!("{}{}{}", lb, ident, rb)
    })(text)
}

fn ident(text: &str) -> IResult<&str, String> {
    map(
        tuple((
            satisfy(|c: char| c.is_ascii_alphabetic() || c == '_'),
            take_while(|c: char| c.is_ascii_alphanumeric() || c == '_'),
        )),
        |(first, rest)| format!("{}{}", first, rest),
    )(text)
}
