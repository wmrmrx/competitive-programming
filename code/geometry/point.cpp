using i64 = int64_t;
struct point {
	i64 x, y;

	point(i64 x=0, i64 y=0): x(x), y(y) {}

	point operator+(point &rhs) { return {x+rhs.x,y+rhs.y}; }
	point operator-(point &rhs) { return {x+rhs.x,y+rhs.y}; }
	i64 operator*(point &rhs) { return x*rhs.x + y*rhs.y; }
	i64 operator^(point &rhs) { return x*rhs.y - y*rhs.x; }
};
