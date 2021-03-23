use std::fs::File;
use std::io::stdout;
use std::io::Read;
use std::io::Write;
use std::process::exit;

mod c;
mod parser;

use parser::parse_input_file;

fn read_input_file() -> String {
    let mut contents = Vec::<u8>::new();
    File::open("../sounds.cc.in")
        .unwrap()
        .read_exact(&mut contents)
        .unwrap();
    String::from_utf8(contents).unwrap()
}

fn main() {
    let input = read_input_file();

    let (_, parsed) = match parse_input_file(input.as_str()) {
        Ok(contents) => contents,
        Err(e) => {
            eprintln!("failed to parse sounds.cc: {}", e);
            exit(1);
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
