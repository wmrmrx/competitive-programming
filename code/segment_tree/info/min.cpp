struct Info {
	using T = int;
	int mn;
	Info(): mn(numeric_limits<T>::max()) {}
	Info(T val): mn(val) {}
	friend Info operator+(Info lhs, Info rhs) {
		Info res(min(lhs.mn, rhs.mn));
		return res;
	}
};
