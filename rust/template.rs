////////////////////////
// BEGIN DEFAULT CODE //
////////////////////////

#[allow(dead_code)]
mod util {
    use std::io::Write;
    static mut BUFFER: String = String::new();

    pub struct Scanner<'a> {
        lock: std::io::StdinLock<'static>,
        tokens: std::str::SplitWhitespace<'a>,
    }

    impl Scanner<'_> {
        pub fn new(lock: std::io::StdinLock<'static>) -> Self {
            Self {
                lock,
                tokens: "".split_whitespace(),
            }
        }

        pub fn new_static(mut lock: std::io::StdinLock<'static>) -> Self {
            use std::io::Read;
            unsafe {
                lock.read_to_string(&mut BUFFER).unwrap();
                Self {
                    lock,
                    tokens: BUFFER.split_whitespace(),
                }
            }
        }

        pub fn read<T: std::str::FromStr<Err = impl std::fmt::Debug>>(&mut self) -> T {
            use std::io::BufRead;
            loop {
                if let Some(s) = self.tokens.next() {
                    return s.parse::<T>().unwrap();
                } else {
                    unsafe {
                        self.tokens = "".split_whitespace();
                        BUFFER.clear();
                        self.lock.read_line(&mut BUFFER).unwrap();
                        self.tokens = BUFFER.split_whitespace()
                    }
                }
            }
        }

        pub fn read_vec<T: std::str::FromStr<Err = impl std::fmt::Debug>>(
            &mut self,
            size: usize,
        ) -> Vec<T> {
            (0..size).map(|_| self.read()).collect()
        }
    }

    impl<'a> Iterator for Scanner<'a> {
        type Item = &'a str;
        fn next(&mut self) -> Option<Self::Item> {
            use std::io::BufRead;
            loop {
                if let Some(s) = self.tokens.next() {
                    return Some(s);
                } else {
                    unsafe {
                        self.tokens = "".split_whitespace();
                        BUFFER.clear();
                        self.lock.read_line(&mut BUFFER).unwrap();
                        self.tokens = BUFFER.split_whitespace()
                    }
                }
            }
        }
    }

    pub struct Writer {
        writer: std::io::BufWriter<std::io::StdoutLock<'static>>,
    }

    impl Writer {
        pub fn new(writer: std::io::BufWriter<std::io::StdoutLock<'static>>) -> Self {
            Self { writer }
        }

        pub fn put<T: std::fmt::Display>(&mut self, t: T) -> &mut Self {
            let _ = write!(self.writer, "{t}");
            self
        }

        pub fn putln<T: std::fmt::Display>(&mut self, t: T) -> &mut Self {
            let _ = writeln!(self.writer, "{t}");
            self
        }

        pub fn ws(&mut self) -> &mut Self {
            let _ = write!(self.writer, " ");
            self
        }

        pub fn endl(&mut self) {
            let _ = writeln!(self.writer);
            self.flush()
        }

        pub fn flush(&mut self) {
            let _ = self.writer.flush();
        }
    }

    pub fn i<S: std::convert::TryInto<usize>>(i: S) -> usize
    where
        <S as std::convert::TryInto<usize>>::Error: std::fmt::Debug,
    {
        i.try_into().unwrap()
    }
}

#[allow(unused_imports)]
use std::{
    collections::{BTreeMap as Map, BTreeSet as Set, VecDeque as Deque},
    format as fmt,
    io::Write,
};
#[allow(unused_imports)]
use util::{i, Scanner, Writer};
type In<'a> = Scanner<'a>;
type Out = Writer;
#[allow(dead_code, non_camel_case_types)]
type u64 = usize;

//////////////////////
// END DEFAULT CODE //
//////////////////////

fn solve(sc: &mut In, bf: &mut Out, gl: &mut Global) {
}

#[derive(Default)]
pub struct Global {
}

fn main() {
    let mut sc = Scanner::new(std::io::stdin().lock());
    let mut out = Writer::new(std::io::BufWriter::new(std::io::stdout().lock()));
    let mut global = Global::default();

    let t: u64 = 1;
    //let t: u64 = sc.read();

    for _ in 0..t {
        solve(&mut sc, &mut out, &mut global);
    }

    out.flush();
}
