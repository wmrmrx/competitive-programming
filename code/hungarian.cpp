constexpr size_t NONE = 1ULL<<60;
bool zero(double x) { return fabs(x) <= 1e-9; }
template <bool MAXIMIZE=false> struct Hungarian {
	vector<vector<double>> w;
	vector<size_t> ml, mr; // ml: matched vertexes of left side
	Hungarian(size_t n): w(n, vector<double>(n)), ml(n), mr(n) {}
	void set(size_t i, size_t j, double weight) { w[i][j] = MAXIMIZE?weight:-weight; }
	double assign() {
		fill(ml.begin(), ml.end(), NONE);
		fill(mr.begin(), mr.end(), NONE);
		uint32_t match = 0; // number of matchings
		size_t n = w.size();
		vector<double> y(n), z(n), d(n);
		vector<size_t> dad(n); 
		vector<bool> S(n), T(n);
		for(size_t i=0;i<n;i++) y[i] = *max_element(w[i].begin(), w[i].end());
		for(size_t i=0;i<n;i++) for(size_t j=0;j<n;j++) {
			if(mr[j] == NONE && zero(w[i][j]-y[i]-z[j])) {
				ml[i] = j; mr[j] = i; match++; break;
			}
		}
		auto update_dual = [&](double delta) {
			for(size_t i=0;i<n;i++) if(S[i]) y[i] -= delta;
			for(size_t j=0;j<n;j++) {
				if(T[j]) z[j] += delta;
				else d[j] -= delta;
			}
		};
		for(;match<n;match++) {
			fill(dad.begin(), dad.end(), NONE);
			fill(S.begin(), S.end(), 0); fill(T.begin(), T.end(), 0);
			size_t i=0, j;
			while(ml[i] != NONE) i++; S[i] = true;
			for(size_t t=0;t<n;t++) d[t] = y[i]+z[t]-w[i][t];
			while(true) {
				j = NONE;
				for(size_t t=0;t<n;t++) if(!T[t] && (j==NONE||d[t]<d[j])) j=t;
				if(!zero(d[j])) {
					update_dual(); 
					continue;
				}
				size_t s = mr[j];
				if(s == NONE) {
					for(s=0;s<n;s++) if(S[s]) {
						if(zero(y[s]+z[j]-w[s][j])) break;
					}
					dad[j] = ml[s];
					break;
				}
				S[s] = true; T[j] = true;
				for(size_t t=0;t<n;t++) if(!T[t]) {
					double val = y[s]+z[t]-w[s][t];
					if(val < d[t]) d[t] = val, dad[t] = j;
				}
			}
			while(dad[j] != NONE) {
				mr[j] = mr[dad[j]];
				ml[mr[j]] = j;
				j = dad[j];
			}
			ml[i] = j; mr[j] = i;
		}
		double ret = 0;
		for(size_t i=0;i<n;i++) ret += w[i][ml[i]];
		return MAXIMIZE?ret:-ret;
	}
};
