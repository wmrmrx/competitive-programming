constexpr int INF = numeric_limits<int>::max();
struct Dinic {
	struct edge {
		int to;
		int cap, flow;
	};

	vector<vector<int>> g;
	vector<int> level;
	vector<edge> e;

	Dinic(int sz): g(sz), level(sz) {}

	void add_edge(int s, int t, int capacity) {
		int id = e.size();
		g[s].push_back(id);
		e.push_back({t, capacity, 0});
		g[t].push_back(++id);
		e.push_back({s, capacity, capacity});
	}

	bool BFS(int source, int sink) {
		fill(level.begin(), level.end(), INF);
		level[source] = 0;
		queue<int> q{{source}};
		while(!q.empty() && level[sink] == INF) {
			int cur = q.front();
			q.pop();
			for(int id: g[cur]) {
				int prox = e[id].to;
				if(level[prox] != INF || e[id].cap == e[id].flow)
					continue;
				level[prox] = level[cur] + 1;
				q.push(prox);
			}
		}
		return level[sink] != INF;
	}

	int DFS(int v, int pool, int start[], int sink) {
		if(pool == 0) return 0;
		if(v == sink) return pool;
		for(;start[v]<(int)g[v].size();start[v]++) {
			int id = g[v][start[v]], prox = e[id].to;
			if(level[v]+1 != level[prox] || e[id].cap == e[id].flow) continue;
			int pushed = DFS(prox,min(e[id].cap-e[id].flow,pool),start,sink);
			if(pushed) {
				e[id].flow += pushed;
				e[id^1].flow -= pushed;
				return pushed;
			}
		}
		return 0;
	}

	int max_flow(int source, int sink) {
		int total_flow = 0;
		vector<int> start(g.size());
		while(BFS(source,sink)) {
			fill(start.begin(), start.end(), 0);
			while(int pushed = DFS(source,INF,start.data(),sink)) 
				total_flow += pushed;
		}
		//reset to initial state
		//for(int i=0;i<e.size();i++) e[i].flow = (i&1) ? e[i].cap : 0;
		return total_flow;
	}
};
