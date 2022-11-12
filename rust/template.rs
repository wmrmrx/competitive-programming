fn solve(sc: &mut In, bf: &mut Out) -> Result<(), Box<dyn std::error::Error>> {
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
use util::{Scanner, i};
type In<'a> = Scanner<'a>;
type Out<'a> = std::io::BufWriter<std::io::StdoutLock<'a>>;
/* END DEFAULT IMPORTS */

#[allow(dead_code, non_camel_case_types)]
type u64 = usize;

#[allow(dead_code)]
mod util {
    static mut INPUT: Option<String> = None;

    pub struct Scanner<'a> {
        lock: std::io::StdinLock<'a>,
        buffer: std::vec::IntoIter<&'a str>,
    }

    impl<'a> Scanner<'a> {
        pub fn new(mut lock: std::io::StdinLock<'a>) -> Self {
            use std::io::BufRead;
            let mut s = String::new();
            lock.read_line(&mut s).unwrap();
            unsafe {
                INPUT = Some(s);
            }
            Scanner {
                lock,
                buffer: unsafe {
                    INPUT
                        .as_ref()
                        .unwrap()
                        .trim()
                        .split_whitespace()
                        .collect::<Vec<&str>>()
                        .into_iter()
                },
            }
        }

        pub fn read<T: std::str::FromStr<Err = impl std::fmt::Debug>>(&mut self) -> T {
            use std::io::BufRead;
            loop {
                if let Some(s) = self.buffer.next() {
                    return s.parse::<T>().unwrap();
                } else {
                    unsafe {
                        self.lock.read_line(INPUT.as_mut().unwrap()).unwrap();
                        self.buffer = INPUT
                            .as_ref()
                            .unwrap()
                            .trim()
                            .split_whitespace()
                            .collect::<Vec<&str>>()
                            .into_iter()
                    }
                }
            }
        }

        pub fn read_vec<T: std::str::FromStr<Err = impl std::fmt::Debug>>(
            &mut self,
            size: usize,
        ) -> Vec<T> {
            return (0..size).map(|_| self.read()).collect();
        }
    }

    pub fn i<S: std::convert::TryInto<usize>>(i: S) -> usize
    where
        <S as std::convert::TryInto<usize>>::Error: std::fmt::Debug,
    {
        return i.try_into().unwrap();
    }
}
