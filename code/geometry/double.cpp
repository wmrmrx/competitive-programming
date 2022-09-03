struct point {
	double x, y;
	
	point(double x=0, double y=0): x(x), y(y) {}
	
	point operator+(point rhs) { return point(x+rhs.x, y+rhs.y); }
	point operator-(point rhs) { return point(x-rhs.x, y-rhs.y); }
	point operator*(double k) { return point(k*x, k*y); }
	double operator*(point rhs) { return x*rhs.x + y*rhs.y; }
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
