////////////////
// BEGIN MINT //
////////////////

#[derive(Clone, Copy, Debug, Default)]
pub struct Mint<const M: u32>(u32);

impl<const M: u32> std::ops::Mul for Mint<M> {
    type Output = Mint<M>;
    fn mul(self, rhs: Self) -> Self::Output {
        (self.0 as usize * rhs.0 as usize % M as usize).into()
    }
}

impl<const M: u32> std::ops::Div for Mint<M> {
    type Output = Mint<M>;
    fn div(self, rhs: Self) -> Self::Output {
        self * rhs.inv()
    }
}

impl<const M: u32> std::ops::Add for Mint<M> {
    type Output = Mint<M>;
    fn add(self, rhs: Self) -> Self::Output {
        if self.0 + rhs.0 < M {
            Mint(self.0 + rhs.0)
        } else {
            Mint(self.0 + rhs.0 - M)
        }
    }
}

impl<const M: u32> std::ops::Sub for Mint<M> {
    type Output = Mint<M>;
    fn sub(self, rhs: Self) -> Self::Output {
        if self.0 >= rhs.0 {
            Mint(self.0 - rhs.0)
        } else {
            Mint(M + self.0 - rhs.0)
        }
    }
}

impl<const M: u32> std::ops::MulAssign for Mint<M> {
    fn mul_assign(&mut self, rhs: Self) {
        *self = *self * rhs;
    }
}

impl<const M: u32> std::ops::DivAssign for Mint<M> {
    fn div_assign(&mut self, rhs: Self) {
        *self = *self / rhs;
    }
}

impl<const M: u32> std::ops::AddAssign for Mint<M> {
    fn add_assign(&mut self, rhs: Self) {
        *self = *self + rhs;
    }
}

impl<const M: u32> std::ops::SubAssign for Mint<M> {
    fn sub_assign(&mut self, rhs: Self) {
        *self = *self - rhs;
    }
}

impl<const M: u32> std::ops::Neg for Mint<M> {
    type Output = Mint<M>;
    fn neg(self) -> Self::Output {
        Mint(M - self.0)
    }
}

impl<const M: u32> From<usize> for Mint<M> {
    fn from(val: usize) -> Mint<M> {
        Mint((val % M as usize) as u32)
    }
}

impl<const M: u32> From<i64> for Mint<M> {
    fn from(val: i64) -> Mint<M> {
        let m = M as i64;
        if val % m < 0 {
            Mint((val % m + m) as u32)
        } else {
            Mint((val % m) as u32)
        }
    }
}

impl<const M: u32> Mint<M> {
    pub fn get(self) -> usize {
        self.0 as usize
    }

    pub fn pow(self, mut e: usize) -> Self {
        let mut res = Mint(1);
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
        self.pow((M - 2) as usize)
    }
}

//////////////
// END MINT //
//////////////
