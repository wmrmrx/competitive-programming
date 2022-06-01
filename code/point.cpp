template <typename T>
struct Point {
	T x,y;

	Point(T x, T y): x(x), y(y) {}

	T dot(Point &rhs) {
		return x*rhs.x + y*rhs.y;
	}

	T cross(Point& rhs) {
		return x*rhs.y - y*rhs.x;
	}

	Point operator+(Point& rhs) { return Point(x+rhs.x,y+rhs.y); }
	Point operator-(Point& rhs) { return Point(x-rhs.x,y-rhs.y); }
	bool operator==(Point& rhs) { return x == rhs.x && y == rhs.y; }
	bool operator<(Point& rhs) {
		if( x != rhs.x ) return x < rhs.x;
		else return y < rhs.y;
	}
};
