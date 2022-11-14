////////////////////////
// BEGIN DEFAULT CODE //
////////////////////////

#[allow(dead_code)]
mod util {
    use std::cell::UnsafeCell;
    use std::io::{BufRead, BufReader, BufWriter, StdinLock, StdoutLock, Write};

    pub struct Scanner<'a> {
        reader: BufReader<StdinLock<'static>>,
        buffer: UnsafeCell<String>,
        tokens: std::str::SplitWhitespace<'a>,
    }

    impl<'a> Iterator for Scanner<'a> {
        type Item = &'a str;
        fn next(&mut self) -> Option<Self::Item> {
            loop {
                if let Some(s) = self.tokens.next() {
                    break Some(s);
                } else {
                    unsafe {
                        self.tokens = "".split_whitespace();
                        self.buffer.get_mut().clear();
                        self.reader.read_line(self.buffer.get_mut()).unwrap();
                        self.tokens = (*self.buffer.get()).split_whitespace();
                    }
                }
            }
        }
    }

    impl Scanner<'_> {
        pub fn new(lock: StdinLock<'static>) -> Self {
            Self {
                reader: BufReader::new(lock),
                buffer: UnsafeCell::new(String::new()),
                tokens: "".split_whitespace(),
            }
        }

        pub fn read<T: std::str::FromStr<Err = impl std::fmt::Debug>>(&mut self) -> T {
            self.tokens.next().unwrap().parse::<T>().unwrap()
        }

        pub fn read_vec<T: std::str::FromStr<Err = impl std::fmt::Debug>>(
            &mut self,
            size: usize,
        ) -> Vec<T> {
            (0..size).map(|_| self.read()).collect()
        }
    }

    pub struct Writer {
        writer: BufWriter<StdoutLock<'static>>,
    }

    impl Writer {
        pub fn new(lock: StdoutLock<'static>) -> Self {
            Self {
                writer: BufWriter::new(lock),
            }
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

#[derive(Debug, Default)]
struct Solver {}

impl Solver {
    fn new() -> Self {
        Self::default()
    }

    fn clean(&mut self) {
        *self = Solver::new();
    }
}

impl Solver {
    fn solve(&mut self, sc: &mut In, bf: &mut Out) {
    }
}

fn main() {
    let mut sc = Scanner::new(std::io::stdin().lock());
    let mut bf = Writer::new(std::io::stdout().lock());
    let mut solver = Solver::new();

    let t: u64 = 1;
    //let t: u64 = sc.read();

    for case in 0..t {
        solver.solve(&mut sc, &mut bf);
        if case != t - 1 {
            solver.clean();
        }
    }
}
