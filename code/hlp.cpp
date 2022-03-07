template <typename SEG> struct HLP {
	struct Node {
		int64_t data;
		size_t seg_handle, seg_root;
		uint32_t prof;
		Node(): data(0), seg_handle(-1), seg_root(-1), prof(0) { }
		size_t seg_pos() {
			return prof-node[seg_root].prof-1;
		}
	};
	const size_t size, root;
	const vector<size_t> g[];
	const LCA lca;
	vector<Node> node;
	vector<SEG> seg;
	HLP(const size_t size, const size_t root, const vector<size_t> g[]): 
		size(size), 
		root(root),
		g(g), 
		lca(size, root, g)
		node(size),
	{
		seg.reserve(size-1);
		vector<uint32_t> sub(size, 1);
		auto dfs_pre = [&](size_t v, size_t parent, auto&& self) {
			for(size_t prox: g[v]) {
				if(prox == parent) continue;
				node[prox].prof = node[v].prof + 1;
				self(prox, v, self);
				sub[v] += sub[prox];
			}
		}
		dfs_pre(root, root, dfs_pre);
		auto dfs_hlp = [&](size_t v, size_t parent, size_t seg_root, auto&& self) -> size_t {
			size_t big_child = -1;
			uint32_t mx = 0;
			if(v != root) {
				if(g[v].size() == 1) {
					node[v].seg_handle = seg.size();
					node[v].seg_root = seg_root;
					seg.push_back(SEG(node[v].prof - node[seg_root].prof));
					return node[v].seg_handle;
				}
				for(size_t prox: g[v]) {
					if(prox == parent) continue;
					if(sub[prox] > mx) {
						mx = sub[prox];
						big_child = prox;
					}
				}
			}
			size_t ret = -1;
			for(size_t prox: g[v]) {
				if(prox == parent) continue;
				if(big_child == prox) {
					ret = self(prox, v, seg_root, self);
				} else {
					self(prox, v, v, self);
				}
			}
			node[v].seg_handle = ret;
			node[v].seg_root = seg_root;
		}
	}
};
