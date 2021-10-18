struct Fraction {
	int num;
	int den;
	Fraction(int _num, int _den) {
		num = _num;
		den = _den;
		if(den < 0) {
			num = -num;
			den = -den;
		}
	}
	bool operator==(Fraction& other) const {
		return (num == other.num && den == other.den);
	}
	bool operator<(Fraction& other) const {
		return num*other.den < other.num*den;
	}
	bool operator<=(Fraction& other) const {
		return num*other.den <= other.num*den;
	}
	bool operator>(Fraction& other) const {
		return num*other.den > other.num*den;
	}
	bool operator>=(Fraction& other) const {
		return num*other.den >= other.num*den;
	}
};
