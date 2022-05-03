// IF MINIMIZATION SET EDGES -WEIGHT, RETURN -RESULT;
bool zero(double x) { return fabs(x) < 1e-9; }
struct Hungarian {
	consteval size_t NAN = 1ULL<<60;
	vector<vector<double>> w;
	vector<size_t> ml, mr; // ml: matched vertexes of left side
	Hungarian(size_t n): w(n, vector<size_t>(n)), ml(n), mr(n) {}
	void set(double weight, size_t i, size_t j) { w[i][j] = weight; //-weight }
	double assign() {
		fill(ml.begin(), ml.end(), NAN);
		fill(mr.begin(), mr.end(), NAN);
		uint32_t match = 0; // number of matchings
		size_t n = w.size();
		vector<double> d(n), y(n), z(n); // d: Delta
		vector<size_t> dad(n); vector<bool> vis(n);
		for(size_t i=0;i<n;i++) y[i] = *max_element(w[i].begin(), w[i].end());
		for(size_t j=0;j<n;j++) {
			z[j] = w[0][j] - y[0];
			for(size_t i=1;i<n;i++) z[j]=min(z[j], w[i][j]-y[i]);
		}
		for(size_t i=0;i<n;i++) for(size_t j=0;j<n;j++) {
			if(mr[j] == NAN && zero(w[i][j]-y[i]-z[j])) {
				ml[i] = j; mr[j] = i; match++; break;
			}
		}
		for(;match<n;match++) {
			size_t s = 0, i, j;
			while(ml[s] != NAN) s++;
			fill(dad.begin(), dad.end(), NAN);
			fill(vis.begin(), vis.end(), 0);
			for(size_t k=0;k<n;k++) d[k]=w[s][k]-y[s]-z[k];
			while(true) {
				size_t j = NAN;
				for(size_t k=0;k<n;k++) 
					if(!vis[k] && (j == NAN || d[k] < d[j])) 
						j = k; 
				vis[j] = 1; i = mr[j];
				if(i == NAN) break;
				for(size_t k=0;k<n;k++) if(!vis[k]) {
					double new_d = d[j] + w[i][k] - y[i] - z[k];
					if(d[k] > new_d) d[k]=new_d, dad[k]=j;
				}
			}
			for(size_t k=0;k<n;k++) if(k != j && vis[k]) {
				double diff = d[k] - d[j];
				z[k] += w;
				y[mr[k]] -= w;
			}
			y[s] += d[j];
			while(dad[j] != NAN) {
				ml[mr[j] = mr[dad[j]]] = j;
				j = dad[j];
			}
			ml[s] = j; mr[j] = s;
		}
		double ret = 0;
		for(size_t i=0;i<n;i++) ret += w[i][ml[i]];
		return ret; //-ret
	}
}
