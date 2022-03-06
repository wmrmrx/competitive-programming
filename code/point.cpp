struct Point {
	int64_t x,y;
	Point(int64_t x, int64_t y): x(x), y(y) {}
	int64_t dot(Point &rhs) const {
		return x*rhs.x + y*rhs.y;
	}
	int64_t cross(Point& rhs) const {
		return x*rhs.y - y*rhs.x;
	}
	Point operator+(Point& rhs) const {
		return Point(x+rhs.x,y+rhs.y);
	}
	Point operator-(Point& rhs) const {
		return Point(x-rhs.x,y-rhs.y);
	}
	bool operator==(Point& rhs) const {
		return x == rhs.x && y == rhs.y;
	}
	bool operator<(Point& rhs) const {
		if( x != rhs.x ) {
			return x < rhs.x;
		} else {
			return y < rhs.y;
		}
	}
};
