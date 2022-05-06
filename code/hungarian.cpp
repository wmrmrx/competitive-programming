constexpr size_t NONE = numeric_limits<size_t>::max();
bool zero(double x) { return fabs(x) < 1e-9; }
template <bool MAXIMIZE=false> struct Hungarian {
	vector<vector<double>> w;
	vector<size_t> ml, mr; // ml: matched vertexes of left side
	Hungarian(size_t n): w(n, vector<double>(n)), ml(n), mr(n) {}
	void set(size_t i, size_t j, double weight) { w[i][j] = MAXIMIZE?weight:-weight; }
	double assign() {
		fill(ml.begin(), ml.end(), NONE);
		fill(mr.begin(), mr.end(), NONE);
		size_t n = w.size();
		vector<double> y(n), z(n), d(n);
		vector<size_t> dad(n); 
		vector<bool> S(n), T(n);
		for(size_t i=0;i<n;i++) y[i] = *max_element(w[i].begin(), w[i].end());
		size_t match = 0; // number of matching
		for(size_t i=0;i<n;i++) for(size_t j=0;j<n;j++) {
			if(mr[j] == NONE && zero(y[i]+z[j]-w[i][j])) {
				ml[i]=j; mr[j]=i; match++; 
				break; 
			}
		} // speedup
		auto update_dual = [&](double delta) {
			for(size_t i=0;i<n;i++) if(S[i]) y[i] -= delta;
			for(size_t j=0;j<n;j++) {
				if(T[j]) z[j] += delta;
				else d[j] -= delta;
			}
		};
		size_t i=0, j;
		for(;match<n;match++) {
			while(ml[i] != NONE) i++;
			fill(S.begin(), S.end(), 0); fill(T.begin(), T.end(), 0);
			S[i] = true;
			for(size_t t=0;t<n;t++) d[t] = y[i]+z[t]-w[i][t];
			fill(dad.begin(), dad.end(), NONE);
			while(true) {
				j = min_element(d.begin(), d.end()) - d.begin();
				if(!zero(d[j])) {
					update_dual(d[j]); 
					continue;
				}
				if(mr[j] == NONE) {
					size_t s=0;
					while(!S[s] || !zero(y[s]+z[j]-w[s][j])) s++;
					dad[j] = ml[s];
					while(dad[j] != NONE) {
						mr[j] = mr[dad[j]];
						ml[mr[j]] = j;
						j = dad[j];
					}
					ml[i] = j; mr[j] = i;
					break;
				} else {
					size_t _i = mr[j];
					S[_i] = true; T[j] = true;
					d[j] = numeric_limits<double>::max();
					for(size_t t=0;t<n;t++) if(!T[t]) {
						double val = y[_i]+z[t]-w[_i][t];
						if(val < d[t]) d[t] = val, dad[t] = j;
					}
				}
			}
		}
		double ret = 0;
		for(i=0;i<n;i++) ret += w[i][ml[i]];
		return MAXIMIZE?ret:-ret;
	}
};
