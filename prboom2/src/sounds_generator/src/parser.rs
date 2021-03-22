use std::ffi::c_void;
use std::fmt::Display;
use std::os::raw::c_int;

use character::complete::char;
use nom::bytes::complete::tag;
use nom::character;
use nom::character::complete::anychar;
use nom::multi::many0;
use nom::sequence::delimited;
use nom::sequence::tuple;
use nom::IResult;

pub struct SoundDefinition {
    pub names: Vec<String>,
    pub singular: bool,
    pub priority: usize,
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
        for lump in self.lump_nums {
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

pub fn parse_input_file(
    text: &str,
) -> Result<Vec<InputSection>, nom::Err<(&str, nom::error::ErrorKind)>> {
    let (text, prefix) = delimited(tag("%%literal"), , tag("%%endliteral"))(text)?;
    let (text, (start, sounds, end)) = tuple((
        tag("sfxinfo_t doom_S_sfx[] = {"),
        parse_sound_definitions,
        tag("};"),
    ))(text)?;
    let (_, suffix) = delimited(tag("%%literal"), many0(anychar), tag("%%endliteral"))(text)?;

}

fn parse_sound_definitions(text: &str) -> IResult<&str, SoundArray> {}
