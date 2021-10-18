struct Fenwick {
	int n;
	vector<int> bit;
	Fenwick(int sz) {
		n = sz;
		bit = vector<int>(n+1);
	}
	void update(int id, int val) {
		while(id <= n) {
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
