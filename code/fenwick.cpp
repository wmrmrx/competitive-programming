template <typename T, bool OneIndexed = true> struct Fenwick {
	const size_t size;
	T* bit;
	Fenwick(size_t size): size(size), bit(new T[size]-1) {}
	~Fenwick() {
		delete [] (bit+1);
	}
	void update(size_t id, const T val) {
		if(!OneIndexed) {
			id += 1;
		}
		while(id <= size) {
			bit[id] += val;
			id += 1ULL<<__builtin_ctzll(id);
		}
	}
	T query(size_t id) {
		if(!OneIndexed) {
			id += 1;
		}
		T sum = 0; 
		while(id > 0) {
			sum += bit[id];
			id -= 1ULL<<__builtin_ctzll(id);
		}
		return sum;
	}
};

