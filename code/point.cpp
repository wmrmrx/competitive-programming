struct Point {
	int64_t x,y;
	Point(int64_t x, int64_t y): x(x), y(y) { }
	int64_t dot(Point &other) const {
		return x*other.x + y*other.y;
	}
	int64_t cross(Point& other) const {
		return x*other.y - y*other.x;
	}
	Point operator+(Point& other) const {
		return Point(x+other.x,y+other.y);
	}
	Point operator-(Point& other) const {
		return Point(x-other.x,y-other.y);
	}
	bool operator==(Point& other) const {
		return x == other.x && y == other.y;
	}
	bool operator<(Point& other) const {
		if( x != other.x ) {
			return x < other.x;
		} else {
			return y < other.y;
		}
	}
};
