struct LCA {
	RMQ<pair<int,int>> *rmq;
	vector<int> time;
	void DFS(int v, int parent, int prof[], vector<pair<int,int>>& euler_tour, vector<int> g[]) {
		time[v] = euler_tour.size();
		euler_tour.push_back({prof[v],v});
		for(auto prox: g[v]) {
			if(prox == parent) {
				continue;
			}
			prof[prox] = prof[v]+1;
			DFS(prox,v,prof,euler_tour,g);
			euler_tour.push_back({prof[v],v});
		}
	}
	LCA(int n, int root, vector<int> g[]) {
		vector<pair<int,int>> euler_tour(1);
		vector<int> prof(n+1);
		time = vector<int>(n+1);
		DFS(root,0,prof.data(),euler_tour,g);
		rmq = new RMQ< pair<int,int> >(2*n-1, euler_tour.data());
	}
	int query(int a, int b) {
		if(time[a] > time[b]) {
			swap(a,b);
		}
		return (rmq->query(time[a],time[b])).second;
	}
};
