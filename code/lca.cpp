struct LCA {
	unique_ptr<RMQ<pair<uint32_t,size_t>>> rmq;
	vector<size_t> time;
	LCA(size_t size, size_t root, const vector<size_t> g[]) {
		vector<pair<uint32_t, size_t>> euler_tour; euler_tour.reserve(2*size-1);
		vector<uint32_t> prof(size); time.assign(size, -1);
		auto dfs = [&](size_t v, size_t parent, auto&& self) {
			time[v] = euler_tour.size();
			euler_tour.push_back({prof[v],v});
			for(size_t prox: g[v]) {
				if(prox == parent) continue;
				prof[prox] = prof[v]+1;
				self(prox,v,self);
				euler_tour.push_back({prof[v],v});
			}
		} 
		dfs(root, root, dfs);
		rmq = RMQ<pair<uint32_t, size_t>>(2*size-1, euler_tour.data());
	}
	size_t query(size_t a, size_t b) const {
		if(time[a] > time[b]) swap(a,b);
		return (rmq->query(time[a],time[b])).second;
	}
};
