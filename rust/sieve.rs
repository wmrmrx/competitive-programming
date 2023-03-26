#[allow(dead_code)]
mod sieve {
    #[derive(Debug)]
    pub struct Sieve<const N: usize> {
        primes: Vec<usize>,
        sieve: Vec<usize>,
    }

    impl<const N: usize> Sieve<N> {
        pub fn new() -> Self {
            let mut res = Self {
                primes: Vec::new(),
                sieve: vec![0; N],
            };
            for i in 2..N {
                if res.sieve[i] == 0 {
                    res.sieve[i] = i;
                    res.primes.push(i);
                    for j in (i * i..N).step_by(i) {
                        if res.sieve[j] == 0 {
                            res.sieve[j] = i;
                        }
                    }
                }
            }
            res
        }

        pub fn primes(&self) -> &[usize] {
            &self.primes
        }

        pub fn is_prime(&self, x: usize) -> bool {
            if x <= N {
                return x > 1 && self.sieve[x] == x;
            }
            for &p in self.primes.iter() {
                if p * p > x {
                    break;
                } else if x % p == 0 {
                    return false;
                }
            }
            true
        }

        /// Returns tuple (prime, exponent)
        pub fn factorization(&self, mut x: usize) -> Vec<(usize, usize)> {
            let mut res = Vec::new();
            if x < N {
                while x > 1 {
                    let p = self.sieve[x];
                    let mut count = 0;
                    while x % p == 0 {
                        count += 1;
                        x /= p;
                    }
                    res.push((p, count));
                }
                return res;
            }
            for &p in self.primes.iter() {
                if p * p > x {
                    break;
                }
                let mut count = 0;
                while x % p == 0 {
                    count += 1;
                    x /= p;
                }
                if count > 0 {
                    res.push((p, count));
                }
            }
            if x > 1 {
                res.push((x, 1));
            }
            res
        }

        pub fn divisors(&self, x: usize) -> Vec<usize> {
            let f = self.factorization(x);
            let mut size = 1;
            for (_, q) in f.iter().cloned() {
                size *= q + 1;
            }
            let mut res = Vec::with_capacity(size);
            res.push(1);
            for (p, q) in f {
                let size = res.len();
                let mut pot = 1;
                for _ in 0..q {
                    pot *= p;
                    for i in 0..size {
                        res.push(res[i] * pot);
                    }
                }
            }
            res
        }
    }
}
type Sieve = sieve::Sieve<300_000>;
