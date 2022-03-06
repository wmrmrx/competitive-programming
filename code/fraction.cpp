struct Fraction {
	int64_t num, den;
	Fraction(int64_t _num, int64_t _den) {
		assert(_den != 0);
		if(den < 0) {
			num = -_num;
			den = -_den;
		} else {
			num = _num;
			den = _den;
		}
	}
	bool operator==(Fraction& rhs) const {
		int64_t l = num*rhs.den;
		int64_t r = rhs.num*den;
		// __int128_t l = (__int128_t) num*rhs.den;
		// __int128_t r = (__int128_t) rhs.num*den;
		return l == r;
	}
	bool operator<(const Fraction& rhs) const {
		int64_t l = num*rhs.den;
		int64_t r = rhs.num*den;
		// __int128_t l = (__int128_t) num*rhs.den;
		// __int128_t r = (__int128_t) rhs.num*den;
		return l < r;
	}
};
