template <typename SEG> struct HLP {
	struct Edge {
		int64_t data;
		size_t seg_handle, seg_pos, seg_root;
		Edge(int64_t data): data(data), seg_handle(0), seg_pos(0), seg_root(0) {}
	};
	int n, root;
	LCA* lca;
	vector<SEG> all_segs; 
	vector<Edge> all_edges;
	vector<vector<Edge*>> edges;
	vector<Edge*> parent_edge;
	vector<vector<int>> g;
	vector<int> sub, parent, prof;
	HLP<SEG>(int _n, int _root) {
		n = _n;
		root = _root;
		all_segs.reserve(n-1); 
		all_edges.reserve(n);
		all_edges.push_back(Edge(0));
		edges = vector<vector<Edge*>>(n+1);
		parent_edge = vector<Edge*>(n+1);
		g = vector<vector<int>>(n+1);
		sub = vector<int>(n+1);
		parent = vector<int>(n+1);
		prof = vector<int>(n+1);
	}
	void add_edge(int s, int t, int data) {
		all_edges.push_back(Edge(data));
		g[s].push_back(t);
		edges[s].push_back(&all_edges.back());
		g[t].push_back(s);
		edges[t].push_back(&all_edges.back());
		if(all_edges.size() == n) {
			init();
		}
	}
	void pre_calc(int v) {
		sub[v] = 1;
		for(auto prox: g[v]) {
			if(prox == parent[v]) {
				continue;
			}
			parent[prox] = v;
			prof[prox] = prof[v]+1;
			pre_calc(prox);
			sub[v] += sub[prox];
		}
	}
	void calc_hlp(int v, int path_root, vector<int>& path) {
		if(g[v].size() == 1 && v != root) {
			all_segs.push_back(SEG(path.size(),path.data()));
			int cur = v;
			for(int d=path.size()-1;d>0;d--) {
				Edge *e = parent_edge[cur];
				e->seg = &all_segs.back();
				e->seg_root = path_root;
				e->seg_pos = d;
				cur = parent[cur];
			}
			return;
		}
		int mx = 0, big_child = 0;
		for(auto prox: g[v]) {
			if(prox == parent[v]) {
				continue;
			}
			if(sub[v] > mx) {
				sub[v] = mx; 
				big_child = prox;
			}
		}
		for(int i=0;i<g[v].size();i++) {
			int prox = g[v][i];
			if(prox == parent[v]) {
				continue;
			}
			Edge *e = edges[v][i];
			parent_edge[prox] = e;
			if(prox == big_child) {
				path.push_back(e->data);
				calc_hlp(prox,path_root,path);
			} else {
				vector<int> new_path(1);
				new_path.push_back(e->data);
				calc_hlp(prox,v,new_path);
			}
		}
	}
	void init() {
		parent_edge[root] = &all_edges[0];
		lca = new LCA(n,root,g.data());
		pre_calc(root);
		vector<int> path(1);
		calc_hlp(root,root,path);
	}
	int jump(int from, int to) {
		int ans = INF;
		while(prof[from] > prof[to]) {
			Edge *fe = parent_edge[from], *te = parent_edge[to];
			if(fe->seg == te->seg) {
				int diff = prof[from] - prof[to] - 1;
				ans = min(ans, fe->seg->query(fe->seg_pos-diff, fe->seg_pos));
				from = to;
			} else {
				ans = min(ans, fe->seg->query(1,fe->seg_pos));
				from = fe->seg_root;
			}
		}
		return ans;
	}
	int query(int a, int b) {
		if(a == b) {
			return INF;
		}
		int c = lca->query(a,b);
		return min(jump(a,c),jump(b,c));
	}
};
