template <typename SEG> struct HLP {
	struct Edge {
		int64_t data;
		size_t seg_handle, seg_root;
		Edge(int64_t data): data(data), seg_handle(-1), seg_root(-1) {}
	};
	const size_t size, root;
	vector<vector<size_t>> g;
	vector<vector<size_t>> edge_id;
	vector<SEG> segs;
	vector<Edge> edges;
	unique_ptr<LCA> lca;
	vector<size_t> parent, parent_edge;
	vector<uint32_t> sub, prof;
	HLP(size_t size, size_t root): size(size), root(root) {
		g.assign(size, vector<size_t>());
		edge_id.assign(size, vector<size_t>());
		segs.reserve(size-1);
		edges.reserve(size-1);
		parent.assign(size, -1);
		parent_edge.assign(size, -1);
		sub.assign(size, -1);
		prof.assign(size, -1);
	}
	void initialize() {
		lca.reset(new LCA(size, root, g.data()));
		auto predfs = [&](size_t cur, auto&& _predfs) -> void {
			sub[cur] = 1;
			for(size_t i=0;i<g[cur].size();i++) {
				size_t prox = g[cur][i];
				size_t edge = edge_id[cur][i];
				if(parent[cur] == prox) {
					continue;
				}
				prof[prox] = prof[cur] + 1;
				parent[prox] = cur;
				parent_edge[prox] = edge;
				_predfs(prox, _predfs);
				sub[cur] += sub[prox];
			}
		};
		prof[root] = 0;
		predfs(root, predfs);
		auto update_edges = [&] (size_t cur, size_t path_root) {
			size_t seg_handle = segs.size(),
			       seg_root = path_root,
			       seg_size = prof[cur] - prof[path_root];
			vector<int64_t> v;
			v.reserve(seg_size);
			while(cur != path_root) {
				Edge &e = edges[parent_edge[cur]];
				v.push_back(e.data);
				e.seg_handle = seg_handle;
				e.seg_root = seg_root;
				cur = parent[cur];
			}
			reverse(v.begin(), v.end());
			segs.push_back(SEG(seg_size, v.data()));

		};
		auto dsudfs = [&](size_t cur, size_t path_root, auto&& _dsudfs) -> void {
			uint32_t max_sub = 0;
			size_t big_child = -1;
			if(cur != root) {
				if(g[cur].size() == 1) {
					update_edges(cur, path_root);
					return;
				}
				for(size_t prox: g[cur]) {
					if(parent[cur] == prox) {
						continue;
					}
					if(sub[prox] > max_sub) {
						big_child = prox;
						max_sub = sub[prox];
					}
				}
			}
			for(size_t i=0;i<g[cur].size();i++) {
				size_t prox = g[cur][i];
				if(parent[cur] == prox) {
					continue;
				}
				if(prox == big_child) {
					_dsudfs(prox, path_root, _dsudfs);
				} else {
					_dsudfs(prox, cur, _dsudfs);
				}
			}
		};
		dsudfs(root, -1, dsudfs);
	}
	// seg position of parent_edge[v]
	size_t seg_pos(size_t v) {
		return prof[v] - prof[edges[parent_edge[v]].seg_root] - 1;
	}
	int64_t query_jump(size_t s, size_t t) {
		int64_t ans = 0;
		while(prof[s] > prof[t]) {
			Edge& e = edges[parent_edge[s]];
			SEG& seg = segs[e.seg_handle];
			if(prof[e.seg_root] >= prof[t]) {
				ans += seg.query(0, seg_pos(s));
				s = e.seg_root;
			} else {
				ans += seg.query(seg_pos(t)+1, seg_pos(s));
				s = t;
			}
		}
		return ans;
	}
	void add_edge(size_t s, size_t t, int64_t data) {
		size_t id = edges.size();
		edges.push_back(Edge(data));
		g[s].push_back(t);
		edge_id[s].push_back(id);
		g[t].push_back(s);
		edge_id[t].push_back(id);
		if(edges.size() == size-1) {
			initialize();
		}
	}
	int64_t query(size_t s, size_t t) {
		size_t ancestor = lca->query(s, t);
		return query_jump(s,ancestor) + query_jump(t, ancestor);
	}
};

