#![allow(non_upper_case_globals)]
#![allow(non_snake_case)]
#![allow(non_camel_case_types)]
#![allow(dead_code)]

use std::ffi::CString;
use std::os::raw::c_char;

include!(concat!(env!("OUT_DIR"), "/bindings.rs"));

pub trait ToCStr {
    fn c_str(&self) -> *const c_char;
}

impl ToCStr for CString {
    fn c_str(&self) -> *const c_char {
        self.as_bytes_with_nul().as_ptr() as *const c_char
    }
}

pub fn convert_str(s: impl AsRef<str>) -> CString {
    CString::new(s.as_ref().to_owned()).unwrap()
}
