#[allow(dead_code)]
mod segtree {
    pub trait Info: Clone + std::fmt::Debug {
        type Basic: Clone + std::fmt::Debug;
        fn new(b: &Self::Basic) -> Self;
        fn zero() -> Self;
        fn merge(&self, rhs: &Self) -> Self;
        fn apply(&mut self, b: &Self::Basic);
    }

    #[derive(Debug)]
    pub struct SegTree<T, const S: bool> {
        size: usize,
        info: Box<[T]>,
    }

    impl<T: Info, const S: bool> SegTree<T, S> {
        fn childs(&self, cur: usize, cl: usize, cr: usize) -> (usize, usize) {
            let m = (cl + cr) / 2;
            (cur + 1, cur + 2*(m - cl + 1))
        }

        fn build(&mut self, cur: usize, cl: usize, cr: usize, v: &[T::Basic]) {
            if cl == cr {
                self.info[cur] = T::new(&v[cl]);
            } else {
                let m = (cl + cr) / 2;
                let (x, y) = self.childs(cur, cl, cr);
                self.build(x, cl, m, v);
                self.build(y, m + 1, cr, v);
                self.info[cur] = self.info[x].merge(&self.info[y]);
            }
        }

        fn pquery(&self, cur: usize, cl: usize, cr: usize, ql: usize, qr: usize) -> T {
            if qr < cl || cr < ql {
                T::zero()
            } else if ql <= cl && cr <= qr {
                self.info[cur].clone()
            } else {
                let m = (cl + cr) / 2;
                let (x, y) = self.childs(cur, cl, cr);
                self.pquery(x, cl, m, ql, qr)
                    .merge(&self.pquery(y, m + 1, cr, ql, qr))
            }
        }

        fn pupdate(&mut self, cur: usize, cl: usize, cr: usize, qp: usize, qv: &T::Basic) {
            if cl == cr {
                if S {
                    self.info[cur] = T::new(qv);
                } else {
                    self.info[cur].apply(qv);
                }
            } else {
                let m = (cl + cr) / 2;
                let (x, y) = self.childs(cur, cl, cr);
                if qp <= m {
                    self.pupdate(x, cl, m, qp, qv);
                } else {
                    self.pupdate(y, m + 1, cr, qp, qv);
                }
                self.info[cur] = self.info[x].merge(&self.info[y]);
            }
        }
    }

    impl<T: Info, const S: bool> SegTree<T, S> {
        pub fn new(size: usize) -> Self {
            Self {
                size,
                info: vec![T::zero(); 2 * size - 1].into_boxed_slice(),
            }
        }

        pub fn from(v: &[T::Basic]) -> Self {
            let size = v.len();
            let mut res = Self {
                size,
                info: vec![T::zero(); 2 * size - 1].into_boxed_slice(),
            };
            res.build(0, 0, size - 1, v);
            res
        }

        pub fn query(&self, l: usize, r: usize) -> T {
            self.pquery(0, 0, self.size - 1, l, r)
        }

        pub fn update(&mut self, pos: usize, val: &T::Basic) {
            self.pupdate(0, 0, self.size - 1, pos, val)
        }
    }

    #[derive(Clone, Debug)]
    pub struct Min(pub i64);

    impl Info for Min {
        type Basic = i64;
        fn new(b: &Self::Basic) -> Self {
            Min(*b)
        }
        fn zero() -> Self {
            Min(i64::MAX)
        }
        fn merge(&self, rhs: &Self) -> Self {
            Min(self.0.min(rhs.0))
        }
        fn apply(&mut self, b: &Self::Basic) {
            self.0 = self.0.min(*b);
        }
    }

    pub type SegMin = SegTree<Min, false>;

    type Number = usize;
    #[derive(Clone, Debug)]
    pub struct MinMax {
        min: Number,
        max: Number,
    }

    pub type SegM = SegTree<MinMax, false>;

    impl Info for MinMax {
        type Basic = Number;
        fn new(b: &Self::Basic) -> Self {
            MinMax { min: *b, max: *b }
        }
        fn zero() -> Self {
            MinMax {
                min: Number::MAX,
                max: Number::MIN,
            }
        }
        fn merge(&self, rhs: &Self) -> Self {
            MinMax {
                min: self.min.min(rhs.min),
                max: self.max.max(rhs.max),
            }
        }
        fn apply(&mut self, b: &Self::Basic) {
            self.min = self.min.min(*b);
            self.max = self.max.max(*b);
        }
    }

    impl SegM {
        fn pbb<const LAST: bool>(
            &self,
            cur: usize,
            cl: usize,
            cr: usize,
            ql: usize,
            qr: usize,
            ok: &impl Fn(&MinMax) -> bool,
        ) -> Option<usize> {
            if qr < cl || cr < ql || (!ok(&self.info[cur])) {
                return None;
            } else if cl == cr {
                return Some(cl);
            }
            let (x, y) = self.childs(cur, cl, cr);
            let m = (cl + cr) / 2;
            let res = if LAST {
                self.pbb::<LAST>(y, m + 1, cr, ql, qr, ok)
            } else {
                self.pbb::<LAST>(x, cl, m, ql, qr, ok)
            };
            if res.is_some() {
                res
            } else if LAST {
                self.pbb::<LAST>(x, cl, m, ql, qr, ok)
            } else {
                self.pbb::<LAST>(y, m + 1, cr, ql, qr, ok)
            }
        }
    }

    impl SegM {
        pub fn first_smaller(&self, l: usize, r: usize, x: Number) -> Option<usize> {
            self.pbb::<false>(0, 0, self.size - 1, l, r, &(|info| info.min < x))
        }

        pub fn first_bigger(&self, l: usize, r: usize, x: Number) -> Option<usize> {
            self.pbb::<false>(0, 0, self.size - 1, l, r, &(|info| info.max > x))
        }

        pub fn last_smaller(&self, l: usize, r: usize, x: Number) -> Option<usize> {
            self.pbb::<true>(0, 0, self.size - 1, l, r, &(|info| info.min < x))
        }

        pub fn last_bigger(&self, l: usize, r: usize, x: Number) -> Option<usize> {
            self.pbb::<true>(0, 0, self.size - 1, l, r, &(|info| info.max > x))
        }
    }
}
use segtree::{SegM, SegMin};
