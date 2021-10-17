void dijkstra(int st, int n, vector<int> grafo[], vector<int> peso[], int dist[]) {
	int d_inf = 1<<30;
	fill(dist+1,dist+n+1,d_inf);
	dist[st] = 0;
	set<pair<int,int>> s;
	for(int i=1;i<=n;i++) {
		s.insert({dist[i],i});
	}
	while(!s.empty()) {
		if(s.begin()->first == d_inf) {
			break;
		}
		int cur = s.begin()->second;
		s.erase(s.begin());
		for(int i=0;i<grafo[cur].size();i++) {
			int prox = grafo[cur][i], w = peso[cur][i];
			if(dist[prox] > dist[cur] + w) {
				s.erase({dist[prox],prox});
				dist[prox] = dist[cur] + w;
				s.insert({dist[prox],prox});
			}
		}
	}
}
