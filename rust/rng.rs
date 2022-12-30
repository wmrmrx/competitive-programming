#[allow(dead_code)]
mod rng {
    /// Source: https://github.com/EbTech/rust-algorithms/blob/master/src/rng.rs
    #[derive(Debug, Clone, PartialEq, Eq)]
    pub struct Xoshiro256PlusPlus {
        s: [u64; 4],
    }

    impl Xoshiro256PlusPlus {
        pub fn new() -> Self {
            let state = ((std::time::SystemTime::now()
                .duration_since(std::time::UNIX_EPOCH)
                .unwrap()
                .as_nanos())
            & ((1 << 64) - 1)) as u64;
            Self::new_from(state)
        }

        pub fn new_from(mut state: u64) -> Self {
            const PHI: u64 = 0x9e3779b97f4a7c15;
            let mut seed = <[u64; 4]>::default();
            for chunk in &mut seed {
                state = state.wrapping_add(PHI);
                let mut z = state;
                z = (z ^ (z >> 30)).wrapping_mul(0xbf58476d1ce4e5b9);
                z = (z ^ (z >> 27)).wrapping_mul(0x94d049bb133111eb);
                z = z ^ (z >> 31);
                *chunk = z;
            }
            Self { s: seed }
        }

        pub fn u32(&mut self) -> u32 {
            (self.u64() >> 32) as u32
        }

        /// Generate a random `u64`.
        #[inline]
        pub fn u64(&mut self) -> u64 {
            let result_plusplus = self.s[0]
                .wrapping_add(self.s[3])
                .rotate_left(23)
                .wrapping_add(self.s[0]);
            let t = self.s[1] << 17;
            self.s[2] ^= self.s[0];
            self.s[3] ^= self.s[1];
            self.s[1] ^= self.s[2];
            self.s[0] ^= self.s[3];
            self.s[2] ^= t;
            self.s[3] = self.s[3].rotate_left(45);
            result_plusplus
        }
    }
}
use rng::Xoshiro256PlusPlus as Rng;
