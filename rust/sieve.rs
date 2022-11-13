#[allow(dead_code)]
mod sieve {
    const N: usize = 300_000;
    static mut SIEVE: [usize; N] = [0; N];
    static mut PRIMES: Vec<usize> = Vec::new();

    pub fn primes() -> &'static [usize] {
        unsafe { &*PRIMES }
    }

    pub fn is_prime(x: usize) -> bool {
        unsafe {
            if x < N {
                return x > 1 && SIEVE[x] == x;
            }
            for &p in PRIMES.iter() {
                if p * p > x {
                    break;
                } else if x % p == 0 {
                    return false;
                }
            }
            true
        }
    }

    /// Returns tuple (prime, exponent)
    pub fn factorization(mut x: usize) -> Vec<(usize, usize)> {
        unsafe {
            let mut res = Vec::new();
            if x < N {
                while x > 1 {
                    let p = SIEVE[x];
                    let mut count = 0;
                    while x % p == 0 {
                        count += 1;
                        x /= p;
                    }
                    res.push((p, count));
                }
                return res;
            }
            for &p in PRIMES.iter() {
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
    }

    #[forbid(dead_code)]
    pub fn init() {
        unsafe {
            for i in 2..N {
                if SIEVE[i] == 0 {
                    SIEVE[i] = i;
                    PRIMES.push(i);
                    for j in (i * i..N).step_by(i) {
                        if SIEVE[j] == 0 {
                            SIEVE[j] = i;
                        }
                    }
                }
            }
        }
    }
}
