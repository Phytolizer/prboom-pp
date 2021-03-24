use std::fmt::Display;
use std::iter::once;
use std::os::raw::c_int;

use pom::parser::*;

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
pub struct SoundArray(Vec<Vec<u8>>);

impl IntoIterator for SoundArray {
    type Item = Vec<u8>;

    type IntoIter = std::vec::IntoIter<Self::Item>;

    fn into_iter(self) -> Self::IntoIter {
        self.0.into_iter()
    }
}

pub struct InputSection {
    pub prefix: Vec<u8>,
    pub sounds: SoundArray,
    pub suffix: Vec<u8>,
}

pub fn parse_input_file<'a>(text: &[u8]) -> Result<InputSection, pom::Error> {
    let parser = literal() + seq(b"sfxinfo_t doom_S_sfx[] = {") + sounds() + seq(b"};")
        - whitespace().opt()
        + literal()
        - whitespace().opt()
        - end();
    parser
        .map(
            |((((literal1, prefix), sounds), suffix), literal2)| InputSection {
                prefix: literal1.into_iter().chain(prefix.iter().cloned()).collect(),
                sounds: SoundArray(sounds),
                suffix: suffix.to_vec(),
            },
        )
        .name("sounds array")
        .parse(text)
}

fn sounds<'a>() -> Parser<'a, u8, Vec<Vec<u8>>> {
    (comment()
        | whitespace()
        | (sound() - sym(b',')).map(|snd| snd.into_iter().chain(b",".iter().cloned()).collect()))
    .repeat(0..)
    .name("sound")
}

fn whitespace<'a>() -> Parser<'a, u8, Vec<u8>> {
    is_a(|c: u8| c.is_ascii_whitespace())
        .repeat(1..)
        .name("whitespace")
}

fn sound<'a>() -> Parser<'a, u8, Vec<u8>> {
    ((array_index() + whitespace().opt() + sym(b'=') + whitespace().opt()).opt()
        * sym(b'{')
        * vector()
        - sym(b',')
        - whitespace().opt()
        + boolean()
        - sym(b',')
        - whitespace().opt()
        + integer()
        - sym(b',')
        - whitespace().opt()
        + ptr()
        - sym(b',')
        - whitespace().opt()
        + integer()
        - sym(b',')
        - whitespace().opt()
        + integer()
        - sym(b',')
        - whitespace().opt()
        + ptr()
        - sym(b',').opt()
        - whitespace().opt()
        - sym(b'}'))
    .map(
        |((((((lumps, singularity), priority), link), pitch), volume), data)| {
            let sep = b", ";
            once(b'{')
                .chain(lumps.into_iter())
                .chain(sep.iter().cloned())
                .chain(singularity.into_iter())
                .chain(sep.iter().cloned())
                .chain(priority.into_iter())
                .chain(sep.iter().cloned())
                .chain(link.into_iter())
                .chain(sep.iter().cloned())
                .chain(pitch.into_iter())
                .chain(sep.iter().cloned())
                .chain(volume.into_iter())
                .chain(sep.iter().cloned())
                .chain(data.into_iter())
                .chain(b"}".iter().cloned())
                .collect()
        },
    )
    .name("sound")
}

fn comment<'a>() -> Parser<'a, u8, Vec<u8>> {
    (seq(b"//") * none_of(b"\n").repeat(0..))
        .map(|s| b"// ".iter().cloned().chain(s.into_iter()).collect())
}

fn boolean<'a>() -> Parser<'a, u8, Vec<u8>> {
    (seq(b"true") | seq(b"false")).map(|s| s.to_vec())
}

fn integer<'a>() -> Parser<'a, u8, Vec<u8>> {
    (sym(b'-').opt() + is_a(|c: u8| c.is_ascii_digit()).repeat(1..))
        .map(|(minus, n)| minus.into_iter().chain(n.into_iter()).collect())
}

fn string<'a>() -> Parser<'a, u8, Vec<u8>> {
    (sym(b'"') * none_of(b"\"").repeat(0..) - sym(b'"')).map(|s| {
        b"\""
            .iter()
            .cloned()
            .chain(s.into_iter())
            .chain(b"\"".iter().cloned())
            .collect()
    })
}

fn ptr<'a>() -> Parser<'a, u8, Vec<u8>> {
    seq(b"nullptr").map(|s| s.to_vec())
        | (sym(b'&') + ident() + array_index().opt()).map(|((amp, ident), ind)| {
            once(amp)
                .chain(ident.into_iter())
                .chain(ind.into_iter().flatten())
                .collect()
        })
}

fn vector<'a>() -> Parser<'a, u8, Vec<u8>> {
    (sym(b'{')
        + list(
            string() | integer(),
            sym(b',') + is_a(|c: u8| c.is_ascii_whitespace()).repeat(0..),
        )
        + sym(b'}'))
    .map(|((lb, ss), rb)| {
        once(lb)
            .chain(
                ss.into_iter()
                    .map(|s: Vec<u8>| {
                        s.into_iter()
                            .chain(b",".iter().cloned())
                            .collect::<Vec<_>>()
                    })
                    .flatten(),
            )
            .chain(once(rb))
            .collect()
    })
}

fn ident<'a>() -> Parser<'a, u8, Vec<u8>> {
    is_a(|c: u8| c.is_ascii_alphanumeric() || c == b'_')
        .repeat(1..)
        .map(|s| s.into_iter().collect())
}

fn array_index<'a>() -> Parser<'a, u8, Vec<u8>> {
    (sym(b'[') + none_of(b"]").repeat(1..) + sym(b']'))
        .map(|((lb, s), rb)| {
            [lb].iter()
                .chain(s.iter())
                .chain([rb].iter())
                .cloned()
                .collect()
        })
        .name("array index")
}

fn literal_start<'a>() -> Parser<'a, u8, ()> {
    seq(b"%%literal").discard().name("literal start tag")
}

fn literal<'a>() -> Parser<'a, u8, Vec<u8>> {
    (whitespace().opt() * literal_start() * not_a(|c: u8| c == b'%').repeat(0..)
        - literal_end()
        - whitespace().opt())
    .name("literal")
}

fn literal_end<'a>() -> Parser<'a, u8, ()> {
    seq(b"%%endliteral\n").discard().name("literal end tag")
}

fn consume<'a>(text: &'a [u8], tag: &[u8]) -> Result<(&'a [u8], &'a [u8]), ()> {
    if text.starts_with(tag) {
        Ok((&text[0..tag.len()], &text[tag.len()..]))
    } else {
        Err(())
    }
}

fn take_while(text: &[u8], predicate: impl Fn(&u8) -> bool) -> (&[u8], &[u8]) {
    let ofs = text.iter().take_while(|&b| predicate(b)).count();
    (&text[..ofs], &text[ofs..])
}

fn take_while1(text: &[u8], predicate: impl Fn(&u8) -> bool) -> Result<(&[u8], &[u8]), ()> {
    let ofs = text.iter().take_while(|&b| predicate(b)).count();
    if ofs == 0 {
        Err(())
    } else {
        Ok((&text[..ofs], &text[ofs..]))
    }
}
