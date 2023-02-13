#[allow(dead_code)]
mod seglazy {
    pub trait Info: Clone {
        type Basic: Clone;
        fn new(b: &Self::Basic) -> Self;
        fn zero() -> Self;
        fn merge(&self, rhs: &Self) -> Self;
        fn put_tag(&mut self, b: &Self::Basic);
        fn propagate(&mut self, c: Option<(&mut Self, &mut Self)>);
    }

    #[derive(Debug)]
    pub struct SegLazy<T> {
        size: usize,
        info: Box<[T]>,
    }

    impl<T: Info> SegLazy<T> {
        fn childs(&self, cur: usize, cl: usize, cr: usize) -> (usize, usize) {
            let m = (cl + cr) / 2;
            (cur + 1, cur + 2 * (m - cl + 1))
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

        fn propagate(&mut self, cur: usize, cl: usize, cr: usize) {
            if cl == cr {
                self.info[cur].propagate(None);
            } else {
                let (x, y) = self.childs(cur, cl, cr);
                let (s1, s2) = self.info.split_at_mut(y);
                let (s0, s1) = s1.split_at_mut(x);
                s0[cur].propagate(Some((&mut s1[0], &mut s2[0])));
            }
        }

        fn pquery(&mut self, cur: usize, cl: usize, cr: usize, ql: usize, qr: usize) -> T {
            self.propagate(cur, cl, cr);
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

        fn pupdate(
            &mut self,
            cur: usize,
            cl: usize,
            cr: usize,
            ql: usize,
            qr: usize,
            qv: &T::Basic,
        ) {
            self.propagate(cur, cl, cr);
            if qr < cl || cr < ql {
                return;
            }
            if ql <= cl && cr <= qr {
                self.info[cur].put_tag(qv);
                self.propagate(cur, cl, cr);
            } else {
                let m = (cl + cr) / 2;
                let (x, y) = self.childs(cur, cl, cr);
                self.pupdate(x, cl, m, ql, qr, qv);
                self.pupdate(y, m + 1, cr, ql, qr, qv);
                self.info[cur] = self.info[x].merge(&self.info[y]);
            }
        }
    }

    impl<T: Info> SegLazy<T> {
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

        pub fn query(&mut self, l: usize, r: usize) -> T {
            self.pquery(0, 0, self.size - 1, l, r)
        }

        pub fn update(&mut self, l: usize, r: usize, val: &T::Basic) {
            self.pupdate(0, 0, self.size - 1, l, r, val)
        }
    }

    #[derive(Clone, Debug)]
    pub struct Min {
        pub min: i64,
        tag: Option<i64>,
    }

    impl Info for Min {
        type Basic = i64;
        fn new(b: &Self::Basic) -> Self {
            Min { min: *b, tag: None }
        }
        fn zero() -> Self {
            Min {
                min: i64::MAX,
                tag: None,
            }
        }
        fn merge(&self, rhs: &Self) -> Self {
            Min {
                min: self.min.min(rhs.min),
                tag: None,
            }
        }
        fn put_tag(&mut self, b: &Self::Basic) {
            if let Some(tag) = self.tag.as_mut() {
                *tag = (*b).min(*tag);
            } else {
                self.tag = Some(*b);
            }
        }
        fn propagate(&mut self, c: Option<(&mut Self, &mut Self)>) {
            if let Some(tag) = self.tag.take() {
                self.min += tag;
                if let Some((x, y)) = c {
                    x.put_tag(&tag);
                    y.put_tag(&tag);
                }
            }
        }
    }
}
use seglazy::SegLazy;
type SegMin = SegLazy<seglazy::Min>;
