struct Fenwick {
	int size;
	vector<int> bit;
	Fenwick(int _size) {
		size = _size;
		bit = vector<int>(size+1);
	}
	Fenwick(int _size, int v[]) {
		size = _size;
		bit = vector<int>(size+1);
		for(int i=1;i<=size;i++) {
			update(i,v[i]);
		}
	}
	void update(int id, int val) {
		while(id <= size) {
			bit[id] += val;
			id += id&-id;
		}
	}
	int query(int id) {
		int sum = 0; 
		while(id > 0) {
			sum += bit[id];
			id -= id&-id;
		}
		return sum;
	}
};
