struct Scanner {
    buffer: std::vec::IntoIter<String>
}

impl Scanner {
    fn new() -> Scanner {
        use std::io::Read;
        let mut s = String::new();
        let _ = std::io::stdin().read_to_string(&mut s);
        Scanner {
            buffer: s.trim().split_whitespace().map(|s| s.to_owned()).collect::<Vec<String>>().into_iter()
        }
    }
    fn next<T: std::str::FromStr<Err = impl std::fmt::Debug>>(&mut self) -> T {
        return self.buffer.next().unwrap().parse::<T>().unwrap();
    }
}

fn solve(scan: &mut Scanner) {
}

fn main() {
    let mut scan = Scanner::new();
    solve(&mut scan);
}
