#[allow(dead_code)]
mod prelude {
    #[allow(unused_imports)]
    use std::{
        cell::UnsafeCell,
        fmt::{Debug, Display},
        io::{BufRead, BufReader, BufWriter, StdinLock, StdoutLock, Write},
    };
    #[derive(Debug)]
    pub struct System {
        reader: BufReader<StdinLock<'static>>,
        writer: BufWriter<StdoutLock<'static>>,
        buffer: UnsafeCell<String>,
        tokens: std::str::SplitWhitespace<'static>,
    }
    impl System {
        pub fn new() -> Self {
            Self {
                reader: BufReader::new(std::io::stdin().lock()),
                writer: BufWriter::new(std::io::stdout().lock()),
                buffer: UnsafeCell::new(String::new()),
                tokens: "".split_whitespace(),
            }
        }
        pub fn read<T: std::str::FromStr<Err = impl Debug>>(&mut self) -> T {
            loop {
                if let Some(s) = self.tokens.next() {
                    break s;
                } else {
                    unsafe {
                        self.tokens = "".split_whitespace();
                        self.buffer.get_mut().clear();
                        self.reader.read_line(self.buffer.get_mut()).unwrap();
                        self.tokens = (*self.buffer.get()).split_whitespace();
                    }
                }
            }
            .parse::<T>()
            .unwrap()
        }
        pub fn read_arr<T: std::str::FromStr<Err = impl Debug>, const N: usize>(
            &mut self,
        ) -> [T; N] {
            std::array::from_fn(|_| self.read())
        }
        pub fn read_raw(&mut self) -> Vec<u8> {
            self.read::<String>().into_bytes()
        }
        pub fn print<T: Display>(&mut self, t: T) -> &mut Self {
            let _ = write!(self.writer, "{t}");
            self
        }
        pub fn println<T: Display>(&mut self, t: T) -> &mut Self {
            let _ = writeln!(self.writer, "{t}");
            self
        }
        pub fn ln(&mut self) -> &mut Self {
            let _ = writeln!(self.writer);
            self
        }
        pub fn ws(&mut self) -> &mut Self {
            let _ = write!(self.writer, " ");
            self
        }
        pub fn flush(&mut self) {
            let _ = self.writer.flush();
        }
    }

    pub fn default<T: std::default::Default>() -> T {
        T::default()
    }
}
use prelude::{default, System};

#[allow(unused_imports)]
use std::collections::{BTreeMap as Map, BTreeSet as Set, BinaryHeap as Heap, VecDeque as Deque};
#[allow(non_camel_case_types, dead_code)]
type u64 = usize;

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#[derive(Debug, Default)]
struct Ctx {
    _adj: Vec<Vec<u64>>,
}

impl Ctx {
    fn new() -> Self {
        default()
    }

    fn reset(&mut self) {}
}

fn solve(sys: &mut System, _ctx: &mut Ctx) {
    sys.println("Hello World!");
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

fn main() {
    let mut sys = System::new();
    let mut ctx = Ctx::new();

    const MULTICASE: bool = false;
    let t: u64 = if MULTICASE { sys.read() } else { 1 };

    for case in 1..=t {
        solve(&mut sys, &mut ctx);
        if case != t {
            ctx.reset();
        }
    }
}
