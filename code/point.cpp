struct Point {
	int x,y;
	Point(int _x, int _y) {
		x = _x;
		y = _y;
	}
	int dot(Point &other) const {
		return x*other.x + y*other.y;
	}
	int cross(Point& other) const {
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
