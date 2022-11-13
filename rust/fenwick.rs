#[allow(dead_code)]
#[derive(Clone, Debug)]
struct Fenwick<T>
where
    T: for<'a> std::ops::AddAssign<&'a T> + Default + std::clone::Clone,
{
    bit: Vec<T>,
}

#[allow(dead_code)]
impl<T> Fenwick<T>
where
    T: for<'a> std::ops::AddAssign<&'a T> + Default + std::clone::Clone,
{
    pub fn new(size: usize) -> Self {
        Self {
            bit: vec![T::default(); size],
        }
    }

    pub fn update(&mut self, mut id: usize, val: T) {
        id += 1;
        while id <= self.bit.len() {
            self.bit[id - 1] += &val;
            id += 1 << id.trailing_zeros();
        }
    }

    pub fn query(&self, mut id: usize) -> T {
        let mut res = T::default();
        id += 1;
        while id > 0 {
            res += &self.bit[id - 1];
            id -= 1 << id.trailing_zeros();
        }
        res
    }
}
