struct LCA {
	const vector<size_t> t;
	const RMQ<pair<uint32_t,size_t>> rmq;
	const pair<vector<size_t>, RMQ<pair<uint32_t,size_t>>> 
		tour(const size_t size, const size_t root, const vector<size_t> g[]) const {
		vector<pair<uint32_t,size_t>> euler_tour; euler_tour.reserve(2*size-1);
		vector<uint32_t> prof(size);
		vector<size_t> time(size);
		const auto dfs = [&](size_t v, size_t parent, const auto& self) -> void {
			time[v] = euler_tour.size();
			euler_tour.push_back({prof[v],v});
			for(size_t prox: g[v]) {
				if(prox == parent) continue;
				prof[prox] = prof[v]+1;
				self(prox,v,self);
				euler_tour.push_back({prof[v],v});
			}
		};
		dfs(root, root, dfs);
		return {time, RMQ<pair<uint32_t, size_t>>(2*size-1, euler_tour.data())};
	}
	LCA(const size_t size, const size_t root, const vector<size_t> g[]): 
		t(tour(size,root,g).first), rmq(tour(size,root,g).second) {}
	size_t query(size_t a, size_t b) const {
		if(t[a] > t[b]) swap(a,b);
		return (rmq.query(t[a],t[b])).second;
	}
};
