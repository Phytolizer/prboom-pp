use std::fs::File;
use std::io::stdout;
use std::io::Read;
use std::io::Write;
use std::process::exit;

mod c;
mod parser;

use parser::parse_input_file;

fn read_input_file() -> Vec<u8> {
    let mut contents = Vec::<u8>::new();
    File::open("../sounds.cc.in")
        .unwrap()
        .read_to_end(&mut contents)
        .unwrap();
    contents
}

fn main() {
    let input = read_input_file();

    let sec = match parse_input_file(&input) {
        Ok(contents) => contents,
        Err(e) => {
            eprintln!("failed to parse sounds.cc: {}", e);
            exit(1);
        }
    };

    let mut f = File::create("../sounds.cc").unwrap();
    print!("Writing {} bytes of prefix...", sec.prefix.len());
    stdout().flush().unwrap();
    f.write(&sec.prefix).unwrap();
    writeln!(f).unwrap();
    println!("Done");

    print!("Expanding parsed section...");
    stdout().flush().unwrap();
    for def in sec.sounds {
        f.write(&def).unwrap();
        writeln!(f).unwrap();
    }
    println!("Done");

    print!("Writing {} bytes of suffix...", sec.prefix.len());
    stdout().flush().unwrap();
    f.write(&sec.suffix).unwrap();
    writeln!(f).unwrap();
    println!("Done");
}
