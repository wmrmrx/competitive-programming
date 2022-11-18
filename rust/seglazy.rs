#[allow(dead_code)]
mod seglazy {
    pub trait Info: Clone + std::fmt::Debug {
        type Basic: Clone + std::fmt::Debug;
        fn new(b: Self::Basic) -> Self;
        fn add(&mut self, b: Self::Basic) -> Self;
        fn zero() -> Self;
        fn merge(self, rhs: Self) -> Self;
        fn tag(&mut self, b: Self::Basic);
        fn propagate(&mut self, c: Option<(&mut Self, &mut Self)>);
    }

    #[derive(Debug)]
    pub struct SegLazy<T: Info> {
        size: usize,
        seg: Vec<T>,
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
                self.seg[cur] = if let Some(v) = v {
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
                self.seg[cur] = self.seg[x].clone().merge(self.seg[y].clone());
            }
        }

        fn propagate(&mut self, cur: usize) {
            let (x, y) = self.c[cur];
            if x == 0 {
                self.seg[cur].propagate(None);
            } else {
                let (s1, s2) = self.seg.split_at_mut(y);
                let (s0, s1) = s1.split_at_mut(x);
                s0[cur].propagate(Some((&mut s1[0], &mut s2[0])));
            }
        }

        fn pquery(&mut self, cur: usize, cl: usize, cr: usize, ql: usize, qr: usize) -> T {
            self.propagate(cur);
            if qr < cl || cr < ql {
                T::zero()
            } else if ql <= cl && cr <= qr {
                self.seg[cur].clone()
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
                if cl == cr {
                    self.seg[cur] = T::new(qv);
                } else {
                    self.seg[cur].tag(qv);
                }
            } else {
                let m = (cl + cr) / 2;
                let (x, y) = self.c[cur];
                self.pupdate(x, cl, m, ql, qr, qv.clone());
                self.pupdate(y, m + 1, cr, ql, qr, qv);
                self.seg[cur] = self.seg[x].clone().merge(self.seg[y].clone());
            }
        }
    }

    impl<T: Info> SegLazy<T> {
        pub fn new(size: usize) -> Self {
            let mut res = Self {
                size,
                seg: vec![T::zero(); 2 * size - 1],
                c: vec![(0, 0); 2 * size - 1],
            };
            res.build(0, 0, size - 1, &mut 0, None);
            res
        }

        pub fn from(v: &[T::Basic]) -> Self {
            let size = v.len();
            let mut res = Self {
                size,
                seg: vec![T::zero(); 2 * size - 1],
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
        fn tag(&mut self, b: Self::Basic) {
            if let Some(tag) = self.tag.as_mut() {
                *tag = b.min(*tag);
            } else {
                self.tag = Some(b);
            }
        }
        fn propagate(&mut self, c: Option<(&mut Self, &mut Self)>) {
            if let Some(tag) = self.tag.take() {
                self.min = tag;
                if let Some((x, y)) = c {
                    x.tag(tag);
                    y.tag(tag);
                }
            }
        }
    }

    #[derive(Clone, Debug)]
    pub struct Sum {
        pub sum: i64,
        tag: Option<i64>,
        len: usize
    }

    impl Info for Sum {
        type Basic: = i64;
        fn new(b: Self::Basic) -> Self {
            Sum {
                sum: b,
                tag: None,
                len: 1
            }
        }
        fn zero() -> Self {
            Sum {
                sum: 0,
                tag: None,
                len: 0
            }
        }
        fn merge(self, rhs: Self) -> Self {
            Sum {
                sum: self.sum + rhs.sum,
                tag: None,
                len: self.len + rhs.len
            }
        }
        fn tag(&mut self, b: Self::Basic) {
            if let Some(tag) = self.tag.as_mut() {
                *tag += b;
            } else {
                self.tag = Some(b);
            }
        }
        fn propagate(&mut self, c: Option<(&mut Self, &mut Self)>) {
            if let Some(tag) = self.tag.take() {
                self.sum += self.len as i64 * tag;
                if let Some((x, y)) = c {
                    x.tag(tag);
                    y.tag(tag);
                }
            }
        }
    }
}

use seglazy::SegLazy;
type SegSum = SegLazy<seglazy::Sum>;

fn main() {
    let mut seg = SegSum::from(&[0, 1, 2, 3, 4]);

    for i in 0..5 {
        println!("{:?}", seg.query(i, i));
    }

    seg.update(0, 4, 1);
    seg.update(2, 2, 100);

    for i in 0..5 {
        for j in i..5 {
            println!("{i} {j} {:?}", seg.query(i, j));
        }
    }
}
