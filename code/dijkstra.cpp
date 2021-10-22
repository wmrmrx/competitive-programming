void dijkstra(int st, int n, vector<int> graph[], vector<int> weight[], int dist[]) {
	fill(dist,dist+n+1,INF);
	dist[st] = 0;
	set<pair<int,int>> s;
	for(int i=1;i<=n;i++) {
		s.insert({dist[i],i});
	}
	while(!s.empty()) {
		if(s.begin()->first == INF) {
			break;
		}
		int cur = s.begin()->second;
		s.erase(s.begin());
		for(int i=0;i<graph[cur].size();i++) {
			int prox = graph[cur][i], w = weight[cur][i];
			if(dist[prox] > dist[cur] + w) {
				s.erase({dist[prox],prox});
				dist[prox] = dist[cur] + w;
				s.insert({dist[prox],prox});
			}
		}
	}
}
