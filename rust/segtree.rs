#[allow(dead_code)]
mod segtree {
    pub trait Info: Clone + std::fmt::Debug {
        type Basic: Clone + std::fmt::Debug;
        fn new(b: Self::Basic) -> Self;
        fn zero() -> Self;
        fn merge(self, rhs: Self) -> Self;
    }

    #[derive(Debug)]
    pub struct SegTree<T: Info> {
        size: usize,
        seg: Vec<T>,
        c: Vec<(usize, usize)>,
    }

    impl<T: Info> SegTree<T> {
        fn build(
            &mut self,
            cur: usize,
            cl: usize,
            cr: usize,
            cnt: &mut usize,
            v: Option<&[T::Basic]>,
        ) {
            if cl == cr {
                self.seg[cur] = if let Some(v) = v {
                    T::new(v[cur].clone())
                } else {
                    T::zero()
                }
            } else {
                let m = (cl + cr) / 2;
                *cnt += 1;
                self.c[cur].0 = *cnt;
                self.build(*cnt, cl, m, cnt, v);
                *cnt += 1;
                self.c[cur].1 = *cnt;
                self.build(*cnt, m + 1, cr, cnt, v);
            }
        }

        fn pquery(&self, cur: usize, cl: usize, cr: usize, ql: usize, qr: usize) -> T {
            if qr < cl || cr < ql {
                T::zero()
            } else if ql <= cl && cr <= qr {
                self.seg[cur].clone()
            } else {
                let m = (cl + cr) / 2;
                let (c1, c2) = self.c[cur];
                self.pquery(c1, cl, m, ql, qr)
                    .merge(self.pquery(c2, m + 1, cr, ql, qr))
            }
        }

        fn pupdate(&mut self, cur: usize, cl: usize, cr: usize, qp: usize, qv: T::Basic) {
            if cl == cr {
                self.seg[cur] = Info::new(qv);
            } else {
                let m = (cl + cr) / 2;
                let (c1, c2) = self.c[cur];
                if qp <= m {
                    self.pupdate(c1, cl, m, qp, qv);
                } else {
                    self.pupdate(c2, m + 1, cr, qp, qv);
                }
                self.seg[cur] = self.seg[c1].clone().merge(self.seg[c2].clone());
            }
        }
    }

    impl<T: Info> SegTree<T> {
        pub fn new(size: usize) -> Self {
            let mut res = Self {
                size,
                seg: vec![T::zero(); 2 * size - 1],
                c: vec![(0, 0); 2 * size - 1],
            };
            res.build(0, 0, size - 1, &mut 0, None);
            res
        }

        pub fn new_from(v: &[T::Basic]) -> Self {
            let size = v.len();
            let mut res = Self {
                size,
                seg: vec![T::zero(); 2 * size - 1],
                c: vec![(0, 0); 2 * size - 1],
            };
            res.build(0, 0, size - 1, &mut 0, Some(v));
            res
        }

        pub fn query(&self, l: usize, r: usize) -> T {
            self.pquery(0, 0, self.size - 1, l, r)
        }

        pub fn update(&mut self, pos: usize, val: T::Basic) {
            self.pupdate(0, 0, self.size - 1, pos, val)
        }
    }

    #[derive(Clone, Debug)]
    pub struct Min {
        pub min: i64,
    }

    impl Info for Min {
        type Basic = i64;
        fn new(b: Self::Basic) -> Self {
            Self { min: b }
        }
        fn zero() -> Self {
            Self { min: i64::MAX }
        }
        fn merge(self, rhs: Self) -> Self {
            Self {
                min: self.min.min(rhs.min),
            }
        }
    }
}

use segtree::{Min, SegTree};
type SegMin = SegTree<Min>;
