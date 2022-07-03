using i64 = int64_t;

struct point {
	using tup = tuple<i64, i64>;
	i64 x, y;

	point(i64 x=0, i64 y=0): x(x), y(y) {}

	point operator+(point rhs) { return {x+rhs.x,y+rhs.y}; }
	point operator-(point rhs) { return {x-rhs.x,y-rhs.y}; }
	i64 operator*(point rhs) { return x*rhs.x+y*rhs.y; }
	i64 operator^(point rhs) { return x*rhs.y-y*rhs.x; }
	bool operator<(const point& rhs) const { return tup{x,y} < tup{rhs.x, rhs.y}; }
	bool operator==(const point& rhs) const { return tup{x,y} == tup{rhs.x, rhs.y}; }
};

// angular comparison in [0, 2pi)
// CORNER CASE: a, b == (0, 0)
bool ang_cmp(point a, point b) {
	auto quad = [](point p) -> bool {
		return p.x < 0 || (p.x == 0 && p.y > 0);
	};
	using tup = tuple<bool, i64>;
	return tup{quad(a), 0} < tup{quad(b), a^b};
}

i64 norm2(point a) {
	return a*a;
}

// squared distance
i64 dist2(point a, point b) {
	return norm2(a-b);
}

// two times signed area of triangle abc
i64 area2(point a, point b, point c) {
	return (b-a)^(c-a);
}

// CORNER CASE: two points are equal
bool left(point a, point b, point c) {
	return area2(a,b,c) > 0;
}

// CORNER CASE: two points are equal
bool right(point a, point b, point c) {
	return area2(a,b,c) < 0;
}

bool collinear(point a, point b, point c) {
	return area2(a,b,c) == 0;
}

// Returns 0 if vectors a and b are not parallel.
// If they are parallel, returns 1 if they have the same direction 
// and returns -1 otherwise
// CORNER CASE: a, b == (0, 0)
int paral(point a, point b) { 
    if((a ^ b) != 0) return 0;
    if((a.x > 0) == (b.x > 0) && (a.y > 0) == (b.y > 0))
        return 1;
    return -1;
}
