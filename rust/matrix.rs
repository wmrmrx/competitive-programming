#[allow(dead_code)]
mod matrix {
    #[derive(Clone, Debug)]
    pub struct Matrix<T> {
        col: usize,
        mat: Box<[T]>,
    }

    impl<T: Clone + Default> Matrix<T> {
        pub fn new(lin: usize, col: usize) -> Self {
            Self {
                col,
                mat: vec![T::default(); lin * col].into_boxed_slice(),
            }
        }

        pub fn swap(&mut self, i1: usize, j1: usize, i2: usize, j2: usize) {
            self.mat.swap(i1 * self.col + j1, i2 * self.col + j2);
        }
    }

    impl<T: Clone + Default> std::ops::Index<usize> for Matrix<T> {
        type Output = [T];
        fn index(&self, index: usize) -> &Self::Output {
            &self.mat[index * self.col..][..self.col]
        }
    }

    impl<T: Clone + Default> std::ops::IndexMut<usize> for Matrix<T> {
        fn index_mut(&mut self, index: usize) -> &mut Self::Output {
            &mut self.mat[index * self.col..][..self.col]
        }
    }
}
use matrix::Matrix;
