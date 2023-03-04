////////////////////////
// BEGIN DEFAULT CODE //
////////////////////////

use std::fmt::Debug;
#[allow(dead_code)]
mod util {
    use std::cell::UnsafeCell;
    use std::io::{BufReader, BufWriter, Read, Write};
    use Debug;

    pub struct IO<'a, R: Read, W: Write> {
        reader: BufReader<R>,
        writer: BufWriter<W>,
        buffer: UnsafeCell<String>,
        tokens: std::str::SplitWhitespace<'a>,
    }

    impl<'a, R: Read, W: Write> Iterator for IO<'a, R, W> {
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

    impl<R: Read, W: Write> IO<'_, R, W> {
        pub fn new(reader: R, writer: W) -> Self {
            Self {
                reader: BufReader::new(reader),
                writer: BufWriter::new(writer),
                buffer: UnsafeCell::new(String::new()),
                tokens: "".split_whitespace(),
            }
        }

        pub fn read<T: std::str::FromStr<Err = impl Debug>>(&mut self) -> T {
            self.next().unwrap().parse::<T>().unwrap()
        }

        pub fn readu(&mut self) -> usize {
            self.read::<usize>()
        }

        pub fn readi(&mut self) -> i64 {
            self.read::<i64>()
        }

        pub fn read_vec<T: std::str::FromStr<Err = impl Debug>>(&mut self, size: usize) -> Vec<T> {
            (0..size).map(|_| self.read()).collect()
        }

        pub fn readu_vec(&mut self, size: usize) -> Vec<usize> {
            self.read_vec::<usize>(size)
        }

        pub fn readi_vec(&mut self, size: usize) -> Vec<i64> {
            self.read_vec::<i64>(size)
        }

        pub fn read_arr<T: std::str::FromStr<Err = impl Debug>, const N: usize>(
            &mut self,
        ) -> [T; N] {
            std::array::from_fn(|_| self.read())
        }

        pub fn readu_arr<const N: usize>(&mut self) -> [usize; N] {
            self.read_arr::<usize, N>()
        }

        pub fn readi_arr<const N: usize>(&mut self) -> [i64; N] {
            self.read_arr::<i64, N>()
        }
    }

    impl<R: Read, W: Write> Write for IO<'_, R, W> {
        fn write(&mut self, buf: &[u8]) -> std::io::Result<usize> {
            self.writer.write(buf)
        }
        fn flush(&mut self) -> std::io::Result<()> {
            self.writer.flush()
        }
    }
}

#[allow(unused_imports)]
use std::{
    collections::{BTreeMap as Map, BTreeSet as Set, BinaryHeap as Heap, VecDeque as Deque},
    io::{Read, Write},
};
use util::IO;
#[allow(dead_code, non_camel_case_types)]
type u64 = usize;

//////////////////////
// END DEFAULT CODE //
//////////////////////

#[derive(Debug)]
struct Solver {}

impl Solver {
    fn new() -> Self {
        Self {}
    }

    fn clean(&mut self) {
        *self = Solver::new();
    }
}

impl Solver {
    fn solve<'a, R: Read, W: Write>(&mut self, io: &mut IO<'a, R, W>) {
    }
}

fn main() {
    let mut io = IO::new(std::io::stdin().lock(), std::io::stdout().lock());
    let mut solver = Solver::new();

    let t: u64 = 1;
    //let t: u64 = sc.read();

    for case in 1..=t {
        solver.solve(&mut io);
        if case != t {
            solver.clean();
        }
    }
}
