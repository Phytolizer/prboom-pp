use std::env;
use std::fs::File;
use std::io::Read;
use std::io::Write;
use std::io::stdout;

mod c;
mod parser;

use c::ToCStr;
use parser::parse_input_file;

fn read_input_file() -> String {
    let mut contents = Vec::<u8>::new();
    File::open(env::var("CMAKE_CURRENT_LIST_DIR").unwrap())
        .unwrap()
        .read_exact(&mut contents)
        .unwrap();
    String::from_utf8(contents).unwrap()
}

fn main() {
    let input = read_input_file();

    let parsed = match parse_input_file(input.as_str()) {
        Ok(contents) => contents,
        Err(e) => {
            unsafe {
                c::I_Error(
                    c::convert_str("failed to parse sounds.cc: %s").c_str(),
                    c::convert_str(e.to_string()).c_str(),
                )
            };
            vec![]
        }
    };
    if parsed.is_empty() {
        return;
    }

    let mut f = File::create("../sounds.cc").unwrap();
    for sec in parsed {
        print!("Writing {} bytes of prefix...", sec.prefix.len());
        stdout().flush().unwrap();
        writeln!(f, "{}", sec.prefix).unwrap();
        println!("Done");

        print!("Expanding parsed section...");
        stdout().flush().unwrap();
        for def in sec.sounds {
            writeln!(f, "{}", def).unwrap();
        }
        println!("Done");

        print!("Writing {} bytes of suffix...", sec.prefix.len());
        stdout().flush().unwrap();
        writeln!(f, "{}", sec.suffix).unwrap();
        println!("Done");
    }
}
