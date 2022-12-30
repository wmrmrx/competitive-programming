#[allow(dead_code)]
mod bitset {
    #[derive(Clone, Debug)]
    pub struct BitSet {
        size: usize,
        v: Vec<u64>,
    }

    impl BitSet {
        pub fn new(size: usize) -> Self {
            Self {
                size,
                v: vec![0; (size + 63) / 64],
            }
        }

        pub fn reset_all(&mut self) {
            for i in self.v.iter_mut() {
                *i = 0;
            }
        }

        pub fn set_all(&mut self) {
            for i in self.v.iter_mut() {
                *i = u64::MAX;
            }
            if let Some(i) = self.v.last_mut() {
                let m = self.size % 64;
                *i = (1 << m) - 1;
            }
        }

        pub fn set(&mut self, idx: usize, b: bool) {
            assert!(idx < self.size);
            let (n, m) = (idx / 64, idx % 64);
            if b {
                self.v[n] |= 1 << m;
            } else {
                self.v[n] &= u64::MAX ^ (1 << m);
            }
        }

        pub fn get(&mut self, idx: usize) -> bool {
            assert!(idx < self.size);
            let (n, m) = (idx / 64, idx % 64);
            self.v[n] & (1 << (m)) != 0
        }

        pub fn count_ones(&mut self) -> usize {
            self.v.iter().map(|i| i.count_ones() as usize).sum()
        }
    }

    impl std::ops::BitAndAssign<&BitSet> for BitSet {
        fn bitand_assign(&mut self, rhs: &BitSet) {
            assert_eq!(self.size, rhs.size);
            for i in 0..self.size {
                self.v[i] &= rhs.v[i];
            }
        }
    }

    impl std::ops::BitOrAssign<&BitSet> for BitSet {
        fn bitor_assign(&mut self, rhs: &BitSet) {
            assert_eq!(self.size, rhs.size);
            for i in 0..self.size {
                self.v[i] |= rhs.v[i];
            }
        }
    }

    impl std::ops::BitXorAssign<&BitSet> for BitSet {
        fn bitxor_assign(&mut self, rhs: &BitSet) {
            assert_eq!(self.size, rhs.size);
            for i in 0..self.size {
                self.v[i] ^= rhs.v[i];
            }
        }
    }
}
use bitset::BitSet;
