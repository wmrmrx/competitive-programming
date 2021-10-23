template <typename SEG> struct HLP {
	struct Edge {
		int data;
		SEG* seg;
		int seg_root, seg_pos;
		Edge(int _data) {
			data = _data;
			seg = NULL;
			seg_pos = seg_root = 0;
		}
	};
	int n, root;
	LCA* lca;
	vector<SEG> all_segs; vector<Edge> all_edges;
	vector<vector<Edge*>> edges;
	vector<Edge*> parent_edge;
	vector<vector<int>> g;
	vector<int> sub, parent, prof;
	HLP<SEG>(int _n, int _root) {
		n = _n;
		root = _root;
		all_segs.reserve(n-1); all_edges.reserve(n);
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
		if(g[v].size() == 1) {
			all_segs.push_back(SEG(path.size(),path.data()));
			int cur = v;
			for(int d=path.size();d>0;d--) {
				all_seg.back()[d-1] = cur;
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
		lca = new LCA(n,root,g);
		pre_calc(root);
		calc_hlp(root,root,vector<int>(1));
	}
	int query(int a, int b) {
		int c = lca->query(a,b);
	}
};
