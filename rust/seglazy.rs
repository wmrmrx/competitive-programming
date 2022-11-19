#[allow(dead_code)]
mod seglazy {
    pub trait Info: Clone + std::fmt::Debug {
        type Basic: Clone + std::fmt::Debug;
        fn new(b: Self::Basic) -> Self;
        fn zero() -> Self;
        fn merge(self, rhs: Self) -> Self;
        fn put_tag(&mut self, b: Self::Basic);
        fn propagate(&mut self, c: Option<(&mut Self, &mut Self)>);
    }

    #[derive(Debug)]
    pub struct SegLazy<T: Info> {
        size: usize,
        info: Vec<T>,
        c: Vec<(usize, usize)>,
    }

    impl<T: Info> SegLazy<T> {
        fn build(
            &mut self,
            cur: usize,
            cl: usize,
            cr: usize,
            cnt: &mut usize,
            v: Option<&[T::Basic]>,
        ) {
            if cl == cr {
                self.info[cur] = if let Some(v) = v {
                    T::new(v[cl].clone())
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
                let (x, y) = self.c[cur];
                self.info[cur] = self.info[x].clone().merge(self.info[y].clone());
            }
        }

        fn propagate(&mut self, cur: usize) {
            let (x, y) = self.c[cur];
            if x == 0 && y == 0 {
                self.info[cur].propagate(None);
            } else {
                let (s1, s2) = self.info.split_at_mut(y);
                let (s0, s1) = s1.split_at_mut(x);
                s0[cur].propagate(Some((&mut s1[0], &mut s2[0])));
            }
        }

        fn pquery(&mut self, cur: usize, cl: usize, cr: usize, ql: usize, qr: usize) -> T {
            self.propagate(cur);
            if qr < cl || cr < ql {
                T::zero()
            } else if ql <= cl && cr <= qr {
                self.info[cur].clone()
            } else {
                let m = (cl + cr) / 2;
                let (x, y) = self.c[cur];
                self.pquery(x, cl, m, ql, qr)
                    .merge(self.pquery(y, m + 1, cr, ql, qr))
            }
        }

        fn pupdate(
            &mut self,
            cur: usize,
            cl: usize,
            cr: usize,
            ql: usize,
            qr: usize,
            qv: T::Basic,
        ) {
            self.propagate(cur);
            if qr < cl || cr < ql {
                return;
            }
            if ql <= cl && cr <= qr {
                self.info[cur].put_tag(qv);
                self.propagate(cur);
            } else {
                let m = (cl + cr) / 2;
                let (x, y) = self.c[cur];
                self.pupdate(x, cl, m, ql, qr, qv.clone());
                self.pupdate(y, m + 1, cr, ql, qr, qv);
                self.info[cur] = self.info[x].clone().merge(self.info[y].clone());
            }
        }
    }

    impl<T: Info> SegLazy<T> {
        pub fn new(size: usize) -> Self {
            let mut res = Self {
                size,
                info: vec![T::zero(); 2 * size - 1],
                c: vec![(0, 0); 2 * size - 1],
            };
            res.build(0, 0, size - 1, &mut 0, None);
            res
        }

        pub fn from(v: &[T::Basic]) -> Self {
            let size = v.len();
            let mut res = Self {
                size,
                info: vec![T::zero(); 2 * size - 1],
                c: vec![(0, 0); 2 * size - 1],
            };
            res.build(0, 0, size - 1, &mut 0, Some(v));
            res
        }

        pub fn query(&mut self, l: usize, r: usize) -> T {
            self.pquery(0, 0, self.size - 1, l, r)
        }

        pub fn update(&mut self, l: usize, r: usize, val: T::Basic) {
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
        fn new(b: Self::Basic) -> Self {
            Min { min: b, tag: None }
        }
        fn zero() -> Self {
            Min {
                min: i64::MAX,
                tag: None,
            }
        }
        fn merge(self, rhs: Self) -> Self {
            Min {
                min: self.min.min(rhs.min),
                tag: None,
            }
        }
        fn put_tag(&mut self, b: Self::Basic) {
            if let Some(tag) = self.tag.as_mut() {
                *tag = b.min(*tag);
            } else {
                self.tag = Some(b);
            }
        }
        fn propagate(&mut self, c: Option<(&mut Self, &mut Self)>) {
            if let Some(tag) = self.tag.take() {
                self.min += tag;
                if let Some((x, y)) = c {
                    x.put_tag(tag);
                    y.put_tag(tag);
                }
            }
        }
    }
}

use seglazy::SegLazy;
type SegMin = SegLazy<seglazy::Min>;
