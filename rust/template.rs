#[allow(dead_code)]
mod util {
    use std::cell::UnsafeCell;
    use std::io::{BufReader, BufWriter, Read, Write};

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

        pub fn read<T: std::str::FromStr<Err = impl std::fmt::Debug>>(&mut self) -> T {
            self.next().unwrap().parse::<T>().unwrap()
        }

        pub fn readu(&mut self) -> usize {
            self.read::<usize>()
        }

        pub fn readi(&mut self) -> i64 {
            self.read::<i64>()
        }

        pub fn read_vec<T: std::str::FromStr<Err = impl std::fmt::Debug>>(
            &mut self,
            size: usize,
        ) -> Vec<T> {
            (0..size).map(|_| self.read()).collect()
        }

        pub fn readu_vec(&mut self, size: usize) -> Vec<usize> {
            self.read_vec::<usize>(size)
        }

        pub fn readi_vec(&mut self, size: usize) -> Vec<i64> {
            self.read_vec::<i64>(size)
        }

        pub fn read_arr<T: std::str::FromStr<Err = impl std::fmt::Debug>, const N: usize>(
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

        pub fn flush(&mut self) {
            let _ = self.writer.flush();
        }
    }
}

#[allow(dead_code)]
mod rec_function {
    //! Copied from https://github.com/EgorKulikov/rust_algo/blob/master/algo_lib/src/misc/recursive_function.rs
    use std::marker::PhantomData;
    macro_rules! recursive_function {
        ($name: ident, $trait: ident, ($($type: ident $arg: ident,)*)) => {
            pub trait $trait<$($type, )*Output> {
                fn call(&mut self, $($arg: $type,)*) -> Output;
            }

            pub struct $name<F, $($type, )*Output>
            where
                F: FnMut(&mut dyn $trait<$($type, )*Output>, $($type, )*) -> Output,
            {
                f: std::cell::UnsafeCell<F>,
                $($arg: PhantomData<$type>,
                )*
                phantom_output: PhantomData<Output>,
            }

            impl<F, $($type, )*Output> $name<F, $($type, )*Output>
            where
                F: FnMut(&mut dyn $trait<$($type, )*Output>, $($type, )*) -> Output,
            {
                pub fn new(f: F) -> Self {
                    Self {
                        f: std::cell::UnsafeCell::new(f),
                        $($arg: Default::default(),
                        )*
                        phantom_output: Default::default(),
                    }
                }
            }

            impl<F, $($type, )*Output> $trait<$($type, )*Output> for $name<F, $($type, )*Output>
            where
                F: FnMut(&mut dyn $trait<$($type, )*Output>, $($type, )*) -> Output,
            {
                fn call(&mut self, $($arg: $type,)*) -> Output {
                    unsafe { (*self.f.get())(self, $($arg, )*) }
                }
            }
        }
    }
    recursive_function!(F0, Callable0, ());
    recursive_function!(F1, Callable1, (A1 a1,));
    recursive_function!(F2, Callable2, (A1 a1, A2 a2,));
    recursive_function!(F3, Callable3, (A1 a1, A2 a2, A3 a3,));
    recursive_function!(F4, Callable4, (A1 a1, A2 a2, A3 a3, A4 a4,));
    recursive_function!(F5, Callable5, (A1 a1, A2 a2, A3 a3, A4 a4, A5 a5,));
    recursive_function!(F6, Callable6, (A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6,));
}
#[allow(unused_imports)]
use rec_function::*;
#[allow(unused_imports)]
use std::{
    collections::{BTreeMap as Map, BTreeSet as Set, BinaryHeap as Heap, VecDeque as Deque},
    io::{Read, Write},
};
use util::IO;
#[allow(dead_code, non_camel_case_types)]
type u64 = usize;

///////////////////////
// END TEMPLATE CODE //
///////////////////////

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
    fn solve<R: Read, W: Write>(&mut self, io: &mut IO<'_, R, W>) {
    }
}

fn main() {
    let mut io = IO::new(std::io::stdin().lock(), std::io::stdout().lock());
    let mut solver = Solver::new();

    let t: u64 = 1;
    //let t: u64 = io.read();

    for case in 1..=t {
        solver.solve(&mut io);
        if case != t {
            solver.clean();
        }
    }
}

