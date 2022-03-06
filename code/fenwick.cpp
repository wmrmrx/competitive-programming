template <bool OneIndexed = true> struct Fenwick {
	const size_t size; vector<int64_t> bit;
	Fenwick(size_t size): size(size), bit(size+1) {}
	void update(size_t id, const int64_t val) {
		for(id+=!OneIndexed;id<=size;id+=id&-id)bit[id]+=val;
	}
	int64_t query(size_t id) {
		size_t sum=0;
		for(id+=!OneIndexed;id>0;id-=id&-id)sum+=bit[id];
		return sum;
	}
};
