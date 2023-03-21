template<typename SEG, bool EDGE> struct HLD {
	int n;
	vector<int> anc, dep, tin, tout, ini, id;
	SEG seg;

	HLD(int _n, vector<int> g[]): 
		n(_n), anc(n), dep(n+1), tin(n), tout(n), ini(n), id(n), seg(n) {
		vector<int> sub(n, 1);
		function<void(int, int)> pre = [&](int u, int p) {
			for(int v: g[u]) if(v != p) {
				dep[v] = dep[u] + 1;
				pre(v, u);
				sub[u] += sub[v];
			}
			for(int i=1;i<int(g[u].size());i++) if(sub[g[u][i]] > sub[g[u][0]])
				swap(g[u][i], g[u][0]);
		};
		pre(0, 0);
		int t = -1, tid = 0;
		function<void(int,int)> dfs = [&](int u, int p) {
			tin[u] = ++t;
			bool fst = true;
			for(int v: g[u]) if(v != p) {
				anc[v] = fst ? anc[u] : u;
				if(fst) ini[v] = ini[u], id[v] = id[u];
				else ini[v] = t, id[v] = ++tid;
				dfs(v, u);
				fst = false;
			}
			tout[u] = t;
		};
		dep[n] = -1;
		anc[0] = n;
		dfs(0, 0);
	}

	// If EDGE, the child u of an edge represents it
	template<typename T> void update(int u, T val) {
		seg.update(tin[u], val);
	}

	template<typename RES> RES query(int u, int v) {
		RES res = RES();
		while(id[u] != id[v]) {
			if(dep[anc[u]] < dep[anc[v]]) swap(u, v);
			res = res + seg.query(ini[u], tin[u]);
			u = anc[u];
		}
		if(tin[u] > tin[v]) swap(u, v);
		// u is now the LCA of u and v
		if(tin[u] + EDGE <= tin[v]) 
			res = res + seg.query(tin[u] + EDGE, tin[v]);
		return res;
	}
};
