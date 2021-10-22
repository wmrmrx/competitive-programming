struct Dinic {
	struct DinicEdge {
		int to, cap, flow;
	};
	int n;
	vector<vector<int>> g;
	vector<DinicEdge> e;
	vector<int> level;
	Dinic(int _n) {
		n = _n;
		g = vector<vector<int>>(n+1);
		level = vector<int>(n+1);
	}
	void add_edge(int s, int t, int capacity) {
		int id = e.size();
		g[s].push_back(id);
		e.push_back({t, capacity, 0});
		g[t].push_back(++id);
		e.push_back({s, capacity, capacity});
	}
	bool BFS(int source, int sink) {
		for(int i=1;i<=n;i++) level[i] = INF;
		level[source] = 0;
		queue<int> q;
		q.push(source);	
		while(!q.empty() && level[sink] == INF) {
			int cur = q.front();
			q.pop();
			for(auto id: g[cur]) {
				int prox = e[id].to;
				if(level[prox] != INF || e[id].cap == e[id].flow)
					continue;
				level[prox] = level[cur] + 1;
				q.push(prox);
			}
		}
		return level[sink] != INF;
	}
	int DFS(int v, int pool, int sink, int start[]) {
		if(pool == 0) 
			return 0;
		if(v == sink)
			return pool;
		for(;start[v]<g[v].size();start[v]++) {
			int id = g[v][start[v]];
			int prox = e[id].to;
			if(level[v]+1 != level[prox] || e[id].cap == e[id].flow)
				continue;
			int pushed = DFS(prox,min(e[id].cap-e[id].flow,pool),sink,start);
			if(pushed == 0)
				continue;
			e[id].flow += pushed;
			e[id^1].flow -= pushed;
			return pushed;
		}
		return 0;
	}
	int max_flow(int source, int sink) {
		int total_flow = 0;
		vector<int> start(n+1);
		while(BFS(source,sink)) {
			fill(start.begin(),start.end(),0);
			while(int pushed = DFS(source,INF,sink,start.data())) { 
				total_flow += pushed;
			}
		}
		return total_flow;
	}
};
