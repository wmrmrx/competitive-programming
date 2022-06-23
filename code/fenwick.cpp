template <typename T>
struct Fenwick {
	vector<T> bit;

	Fenwick(int sz): sz(sz), bit(sz+1) {}

	void update(int id, T val) {
		for(;id<(int)bit.size();id+=id&-id) bit[id]+=val;
	}

	T query(int id) {
		T sum = 0;
		for(;id>0;id-=id&-id) sum+=bit[id];
		return sum;
	}
};
