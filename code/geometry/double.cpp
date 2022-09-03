#include <bits/stdc++.h>
using namespace std;

struct point {
	double x, y;
	
	point(double x=0, double y=0): x(x), y(y) {}
	
	point operator+(point rhs) { return point(x+rhs.x, y+rhs.y); }
	point operator-(point rhs) { return point(x-rhs.x, y-rhs.y); }
	point operator*(double k) { return point(k*x, k*y); }
	double operator*(point rhs) { return x*rhs.x + y*rhs.y; }

	using tup = tuple<double, double>;

	bool operator<(const point& rhs) const {
		return tup{x, y} < tup{rhs.x, rhs.y};
	}
};

struct segment {
	point a, b;
	segment(point a=point(), point b=point()): a(a), b(b) {}
};

point proj(segment r, point p) {
	auto [a, b] = r;
	p = p - a;
	point v = b-a;
	return a + v*((p*v)/(v*v));
}

signed main() {
	ios::sync_with_stdio(false); cin.tie(0);

	point p = proj(segment(point(0,2), point(1,2)), point(1512,1));
	cout << p.x << ' ' << p.y << endl;
}
