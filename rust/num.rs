#[allow(dead_code)]
mod num {
    pub fn gcd(a: usize, b: usize) -> usize {
        if a == 0 {
            return b;
        }
        let mut t = (a, b);
        while t.1 != 0 {
            t = (t.1, t.0 % t.1);
        }
        t.0
    }
}
