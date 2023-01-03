#[allow(dead_code)]
mod fenwick {
    #[derive(Clone, Debug)]
    pub struct Fenwick<T> {
        bit: Vec<T>,
    }

    impl<T> Fenwick<T>
    where
        T: Default + std::clone::Clone + std::marker::Copy + std::ops::Add<Output = T>,
    {
        pub fn new(size: usize) -> Self {
            Self {
                bit: vec![T::default(); size],
            }
        }

        pub fn update(&mut self, mut id: usize, val: T) {
            id += 1;
            while id <= self.bit.len() {
                self.bit[id - 1] += val;
                id += 1 << id.trailing_zeros();
            }
        }

        pub fn query(&self, mut id: usize) -> T {
            let mut res = T::default();
            id += 1;
            while id > 0 {
                res = res + self.bit[id - 1];
                id -= 1 << id.trailing_zeros();
            }
            res
        }
    }

    impl<T> Fenwick<T>
    where
        T: Default
            + std::clone::Clone
            + std::marker::Copy
            + std::ops::Add<Output = T>
            + std::ops::Sub<Output = T>,
    {
        pub fn range(&self, l: usize, r: usize) -> T {
            self.query(r)
                - if l == 0 {
                    T::default()
                } else {
                    self.query(l - 1)
                }
        }
    }
}
use fenwick::Fenwick;
