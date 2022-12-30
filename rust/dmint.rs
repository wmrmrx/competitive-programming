#[allow(dead_code)]
mod dmint {
    #[derive(Clone, Copy, Debug)]
    pub struct DMint(u32, u32);

    impl std::ops::Mul for DMint {
        type Output = DMint;
        fn mul(self, rhs: Self) -> Self::Output {
            assert_eq!(self.1, rhs.1);
            let m = self.1 as usize;
            DMint(((self.0 as usize * rhs.0 as usize % m) % m) as u32, self.1)
        }
    }

    impl std::ops::Div for DMint {
        type Output = DMint;
        fn div(self, rhs: Self) -> Self::Output {
            assert_eq!(self.1, rhs.1);
            self * rhs.inv()
        }
    }

    impl std::ops::Add for DMint {
        type Output = DMint;
        fn add(self, rhs: Self) -> Self::Output {
            assert_eq!(self.1, rhs.1);
            let m = self.1;
            if self.0 + rhs.0 < m {
                DMint(self.0 + rhs.0, m)
            } else {
                DMint(self.0 + rhs.0 - m, m)
            }
        }
    }

    impl std::ops::Sub for DMint {
        type Output = DMint;
        fn sub(self, rhs: Self) -> Self::Output {
            assert_eq!(self.1, rhs.1);
            let m = self.1;
            if self.0 >= rhs.0 {
                DMint(self.0 - rhs.0, m)
            } else {
                DMint(m + self.0 - rhs.0, m)
            }
        }
    }

    impl std::ops::MulAssign for DMint {
        fn mul_assign(&mut self, rhs: Self) {
            *self = *self * rhs;
        }
    }

    impl std::ops::DivAssign for DMint {
        fn div_assign(&mut self, rhs: Self) {
            *self = *self / rhs;
        }
    }

    impl std::ops::AddAssign for DMint {
        fn add_assign(&mut self, rhs: Self) {
            *self = *self + rhs;
        }
    }

    impl std::ops::SubAssign for DMint {
        fn sub_assign(&mut self, rhs: Self) {
            *self = *self - rhs;
        }
    }

    impl std::ops::Neg for DMint {
        type Output = DMint;
        fn neg(self) -> Self::Output {
            DMint(self.1 - self.0, self.1)
        }
    }

    impl DMint {
        pub fn new(val: i64, m: usize) -> Self {
            if val >= 0 {
                DMint((val % m as i64) as u32, m as u32)
            } else {
                -DMint(((-val) as usize % m) as u32, m as u32)
            }
        }

        pub fn get(self) -> usize {
            self.0 as usize
        }

        pub fn pow(self, mut e: usize) -> Self {
            let mut res = DMint(1, self.1);
            let mut pot = self;
            while e > 0 {
                if e % 2 == 1 {
                    res *= pot;
                }
                pot *= pot;
                e /= 2;
            }
            res
        }

        pub fn inv(self) -> Self {
            self.pow((self.1 - 2) as usize)
        }
    }
}
use dmint::DMint;
