struct dsu {
	vector<int> dad, sz;
	dsu(int n) {
		dad = vector<int>(n);
		iota(all(dad), 0);
		sz = vector<int>(n, 1);
	}
	int find(int v) {
		return v == dad[v] ? v : dad[v] = find(dad[v]);
	}
	void join(int u, int v) {
		u = find(u);
		v = find(v);
		if(u != v) {
			if(sz[u] > sz[v]) swap(u,v);
			dad[u] = v;
			sz[v] += sz[u];
		}
	}
	bool same(int u, int v) {
		return find(u) == find(v);
	}
	void reset() {
		iota(all(dad), 0);
		fill(all(sz), 0);
	}
};
