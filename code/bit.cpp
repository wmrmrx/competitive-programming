template <typename T>
struct Bit {
	vector<T> bit;
	Bit(int sz): bit(sz) {}
	void update(int id, T val) {
		for(id++;id<(int)bit.size();id+=id&-id) bit[id-1]+=val;
	}
	T query(int id) {
		T sum = 0;
		for(id++;id>0;id-=id&-id) sum+=bit[id-1];
		return sum;
	}
};
