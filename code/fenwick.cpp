template <template typename T, bool OneIndexed = true> struct Fenwick {
	const size_t size; vector<T> bit;
	Fenwick(size_t size): size(size), bit(size+1) {}
	void update(size_t id, const T val) {
		for(id+=!OneIndexed;id<=size;id+=id&-id)bit[id]+=val;
	}
	T query(size_t id) {
		T sum=0;
		for(id+=!OneIndexed;id>0;id-=id&-id)sum+=bit[id];
		return sum;
	}
};
