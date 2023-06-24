int n;
vector<pair<int,int>> g[N];
namespace tarjan {
	stack<int, vector<int>> st;
	int ncomp;
	int cnt;
	int low[N], in[N], comp[N];
 
	void dfs(int u) { 
		low[u] = in[u] = ++cnt;
		st.push(u);
		for(auto [v, _]: g[u]) {
			if(in[v] == 0) {
				dfs(v);
				low[u] = min(low[u], low[v]);
			} else if(!comp[v]) {
				low[u] = min(low[u], in[v]);
			}
		}
		if(low[u] == in[u]) {
			ncomp++;
			int top;
			do {
				top = st.top();
				st.pop();
				comp[top] = ncomp;
			} while(top != u);
		}
	}
 
	void init() {
		for(int i=0;i<n;i++) if(in[i] == 0) {
			dfs(i);
		}
		for(int i=0;i<n;i++) comp[i]--;
	}
}
