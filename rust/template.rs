fn solve(sc: &mut In, bf: &mut Out) -> Ignore {
    Ok(())
}

fn main() {
    let mut sc = Scanner::new(std::io::stdin().lock());
    let mut out = std::io::BufWriter::new(std::io::stdout().lock());
    solve(&mut sc, &mut out).unwrap();
    out.flush().unwrap();
}

////////////////////////
// BEGIN DEFAULT CODE //
////////////////////////

#[allow(unused_imports)]
use std::{
    collections::{BTreeMap as Map, BTreeSet as Set},
    io::Write,
};
#[allow(unused_imports)]
use util::{i, Scanner};
type In<'a> = Scanner<'a>;
type Out<'a> = std::io::BufWriter<std::io::StdoutLock<'a>>;
type Ignore = Result<(), Box<dyn std::error::Error>>;

#[allow(dead_code, non_camel_case_types)]
type u64 = usize;

#[allow(dead_code)]
mod util {
    pub struct Scanner<'a> {
        lock: std::io::StdinLock<'static>,
        buffer: *mut String,
        tokens: std::str::SplitWhitespace<'a>,
    }

    impl Scanner<'_> {
        pub fn new(lock: std::io::StdinLock<'static>) -> Self {
            Self {
                lock,
                buffer: Box::into_raw(Box::new(String::new())),
                tokens: "".split_whitespace(),
            }
        }

        pub fn read<T: std::str::FromStr<Err = impl std::fmt::Debug>>(&mut self) -> T {
            use std::io::BufRead;
            loop {
                if let Some(s) = self.tokens.next() {
                    return s.parse::<T>().unwrap();
                } else {
                    unsafe { &mut *self.buffer }.clear();
                    self.lock.read_line(unsafe { &mut *self.buffer }).unwrap();
                    self.tokens = unsafe { &*self.buffer }.split_whitespace()
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
                    unsafe { &mut *self.buffer }.clear();
                    self.lock.read_line(unsafe { &mut *self.buffer }).unwrap();
                    self.tokens = unsafe { &*self.buffer }.split_whitespace()
                }
            }
        }
    }

    pub fn i<S: std::convert::TryInto<usize>>(i: S) -> usize
    where
        <S as std::convert::TryInto<usize>>::Error: std::fmt::Debug,
    {
        i.try_into().unwrap()
    }
}
