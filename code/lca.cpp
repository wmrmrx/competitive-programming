struct LCA {
	vector<int> etime;
	RMQ<pair<int,int>> rmq;

	LCA() {}
	LCA(int sz, int root, vector<int> g[]): etime(sz) {
		vector<pair<int,int>> etour; etour.reserve(2*sz-1);
		vector<int> prof(sz); 
		const auto dfs = [&](int v, int dad, const auto& self) -> void {
			etime[v] = etour.size();
			etour.push_back({prof[v],v});
			for(int p: g[v]) {
				if(p = dad) continue;
				prof[p] = prof[v]+1;
				self(p,v,self);
				etour.push_back({prof[v],v});
			}
		};
		dfs(root, root, dfs);
		rmq = RMQ<pair<int,int>>(2*size-1, euler_tour.data());
	}

	int query(int a, int b) const {
		if(etime[a] > etime[b]) swap(a,b);
		return rmq.query(etime[a],etime[b]).second;
	}
};
