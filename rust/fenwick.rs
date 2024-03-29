#[allow(dead_code)]
mod fenwick {
    #[derive(Clone, Debug)]
    pub struct Fenwick<T> {
        bit: Box<[T]>,
    }

    impl<T> Fenwick<T>
    where
        T: Default + Clone + Copy + std::ops::Add<Output = T>,
    {
        pub fn new(size: usize) -> Self {
            Self {
                bit: vec![T::default(); size].into_boxed_slice(),
            }
        }

        pub fn update(&mut self, mut id: usize, val: T) {
            id += 1;
            while id <= self.bit.len() {
                self.bit[id - 1] = self.bit[id - 1] + val;
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
        T: Default + Clone + Copy + std::ops::Add<Output = T> + std::ops::Sub<Output = T>,
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
