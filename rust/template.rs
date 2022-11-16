////////////////////////
// BEGIN DEFAULT CODE //
////////////////////////

#[allow(dead_code)]
mod util {
    use std::cell::UnsafeCell;
    use std::io::{BufReader, BufWriter, Read, Write};

    pub struct Scanner<'a, R: Read> {
        reader: BufReader<R>,
        buffer: UnsafeCell<String>,
        tokens: std::str::SplitWhitespace<'a>,
    }

    impl<'a, R: Read> Iterator for Scanner<'a, R> {
        type Item = &'a str;
        fn next(&mut self) -> Option<Self::Item> {
            use std::io::BufRead;
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

    impl<R: Read> Scanner<'_, R> {
        pub fn new(reader: R) -> Self {
            Self {
                reader: BufReader::new(reader),
                buffer: UnsafeCell::new(String::new()),
                tokens: "".split_whitespace(),
            }
        }

        pub fn read<T: std::str::FromStr<Err = impl std::fmt::Debug>>(&mut self) -> T {
            self.next().unwrap().parse::<T>().unwrap()
        }

        pub fn read_vec<T: std::str::FromStr<Err = impl std::fmt::Debug>>(
            &mut self,
            size: usize,
        ) -> Vec<T> {
            (0..size).map(|_| self.read()).collect()
        }
    }

    pub struct Writer<W: Write> {
        writer: BufWriter<W>,
    }

    impl<W: Write> Writer<W> {
        pub fn new(writer: W) -> Self {
            Self {
                writer: BufWriter::new(writer),
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
    io::{Read, Write},
};
#[allow(unused_imports)]
use util::{i, Scanner, Writer};
type In<'a, R> = Scanner<'a, R>;
type Out<W> = Writer<W>;
#[allow(dead_code, non_camel_case_types)]
type u64 = usize;

//////////////////////
// END DEFAULT CODE //
//////////////////////

#[derive(Debug)]
struct Solver {
}

impl Solver {
    fn new() -> Self {
        Self {
        }
    }

    fn clean(&mut self) {
        *self = Solver::new();
    }
}

impl Solver {
    fn solve<R: Read, W: Write>(&mut self, sc: &mut In<R>, bf: &mut Out<W>) {
    }
}

fn main() {
    let mut sc = Scanner::new(std::io::stdin().lock());
    let mut bf = Writer::new(std::io::stdout().lock());
    let mut solver = Solver::new();

    let t: u64 = 1;
    //let t: u64 = sc.read();

    for case in 1..=t {
        solver.solve(&mut sc, &mut bf);
        if case != t {
            solver.clean();
        }
    }
}
