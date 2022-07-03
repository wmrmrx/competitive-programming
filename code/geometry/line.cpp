// CORNER CASE: a == b
struct line {
	using tup = tuple<point, point>;
	point a, b;

	line(point a={0,0}, point b={0,0}): a(min(a,b)), b(max(a,b)) {}

	bool has(point p) {
		return a == p || b == p || paral(a-p, b-p) == -1;
	}

	bool intersects(line rhs) {
		if(has(rhs.a) || has(rhs.b) || rhs.has(a) || rhs.has(b)) return 1;
		return left(a,b,rhs.a) != left(a,b,rhs.b) && 
			left(rhs.a, rhs.b, a) != left(rhs.a, rhs.b, b);
	}

	bool operator==(const line&& rhs) const { return tup{a,b} == tup{rhs.a,rhs.b}; }
};
