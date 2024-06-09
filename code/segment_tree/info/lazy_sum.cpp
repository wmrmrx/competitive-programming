struct Info {
	using T = int;
	int x;
	Info(): x(numeric_limits<T>::max()) {}
	Info(T val): x(val) {}
	friend Info operator+(const Info lhs, const Info rhs) {
		Info res;
		res.x = min(lhs.x, rhs.x);
		return res;
	}

	using U = int;
	struct Tag {
		int tag;
		Tag(): tag(0) {}
		Tag(U val): tag(val) {}
		void operator+=(Tag rhs) {
			tag += rhs.tag;
		}
		void apply(Info& info, const int l, const int r) const {
			info.x += tag;
		}
	};
};


