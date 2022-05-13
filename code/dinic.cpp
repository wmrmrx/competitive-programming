struct Dinic {
	const uint64_t INF = 1ULL<<63;
	struct Edge {
		size_t to;
		uint64_t cap, flow;
	};
	vector<vector<size_t>> g;
	vector<Edge> e;
	vector<uint64_t> level;
	Dinic(size_t size) {
		g.assign(size, vector<size_t>());
		level.assign(size, -1);
		e.reserve(size);
	}
	void add_edge(size_t s, size_t t, uint64_t capacity) {
		int id = e.size();
		g[s].push_back(id);
		e.push_back({t, capacity, 0});
		g[t].push_back(++id);
		e.push_back({s, capacity, capacity});
	}
	bool BFS(size_t source, size_t sink) {
		fill(level.begin(), level.end(), 0);
		level[source] = 0;
		queue<size_t> q;
		q.push(source);	
		while(!q.empty() && level[sink] == INF) {
			size_t cur = q.front();
			q.pop();
			for(size_t id: g[cur]) {
				size_t prox = e[id].to;
				if(level[prox] != INF || e[id].cap == e[id].flow)
					continue;
				level[prox] = level[cur] + 1;
				q.push(prox);
			}
		}
		return level[sink] != INF;
	}
	uint64_t DFS(size_t v, uint64_t pool, size_t sink, size_t start[]) {
		if(pool == 0) {
			return 0;
		}
		if(v == sink) {
			return pool;
		}
		for(;start[v]<g[v].size();start[v]++) {
			size_t id = g[v][start[v]];
			size_t prox = e[id].to;
			if(level[v]+1 != level[prox] || e[id].cap == e[id].flow)
				continue;
			uint64_t pushed = DFS(prox,min(e[id].cap-e[id].flow,pool),sink,start);
			if(pushed == 0) {
				continue;
			}
			e[id].flow += pushed;
			e[id^1].flow -= pushed;
			return pushed;
		}
		return 0;
	}
	//void reset() {
	//	for(size_t i=0;i<e.size();i++) {
	//		if(i&1) {
	//			e[i].flow = e[i].cap;
	//		} else {
	//			e[i].flow = 0;
	//		}
	//	}
	//}
	uint64_t max_flow(size_t source, size_t sink) {
		uint64_t total_flow = 0;
		vector<size_t> start(g.size());
		while(BFS(source,sink)) {
			fill(start.begin(),start.end(),0);
			uint64_t pushed;
			while((pushed = DFS(source,INF,sink,start.data())) > 0) { 
				total_flow += pushed;
			}
		}
		//reset();
		return total_flow;
	}
};
