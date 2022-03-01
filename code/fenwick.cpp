template <typename T, bool OneIndexed = true> struct Fenwick {
	vector<T> bit;
	Fenwick(size_t size) {
		bit.assign(size, 0);
	}
	void update(size_t id, const T val) {
		if(!OneIndexed) {
			id += 1;
		}
		while(id <= size) {
			bit[id-1] += val;
			id += 1ULL<<__builtin_ctzll(id);
		}
	}
	T query(size_t id) {
		if(!OneIndexed) {
			id += 1;
		}
		T sum = 0; 
		while(id > 0) {
			sum += bit[id-1];
			id -= 1ULL<<__builtin_ctzll(id);
		}
		return sum;
	}
};
