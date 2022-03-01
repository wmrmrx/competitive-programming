// ONE INDEXED
template <typename T> struct Fenwick {
	const size_t size;
	vector<T> bit;
	Fenwick(size_t size): size(size) {
		bit = vector<T>(size+1);
	}
	void update(size_t id, const T val) {
		while(id <= size) {
			bit[id] += val;
			id += 1ULL<<__builtin_ctzll(id);
		}
	}
	T query(size_t id) {
		T sum = 0; 
		while(id > 0) {
			sum += bit[id];
			id -= 1ULL<<__builtin_ctzll(id);
		}
		return sum;
	}
};
