// IF MINIMIZING BE CAREFUL WITH 0 WEIGHT EDGES!!!
// (INITIALIZE W WITH INF)
constexpr size_t NONE = numeric_limits<size_t>::max();
bool zero(double x) { return abs(x) < 1e-9; }
template <bool MAXIMIZE> struct Hungarian {
	vector<vector<double>> w;
	vector<size_t> ml, mr; // ml: matched vertexes of left side
	vector<double> y, z, d;
	vector<bool> S, T;
	Hungarian(size_t n): w(n,vector<double>(n,0/*1e100*/)),ml(n),mr(n),y(n),z(n),d(n),S(n),T(n) {}
	void set(size_t i, size_t j, double weight) { w[i][j] = MAXIMIZE?weight:-weight; }
	double assign() {
		size_t n = w.size();
		ml.assign(n, NONE); mr.assign(n, NONE);
		for(size_t i=0;i<n;i++) y[i] = *max_element(w[i].begin(), w[i].end());
		z.assign(n, 0);
		for(size_t i=0;i<n;i++) for(size_t j=0;j<n;j++) {
			if(mr[j] == NONE && zero(y[i]+z[j]-w[i][j])) {
				ml[i] = j; mr[j] = i;
				break;
			}
		}
		auto kuhn = [&](size_t s, auto&& self) -> bool {
			if(S[s]) return false; S[s] = 1;
			for(size_t t=0;t<n;t++) {
				double diff = y[s]+z[t]-w[s][t];
				if(T[t]) continue;
				if(zero(diff)) {
					T[t] = 1;
					if(mr[t] == NONE || self(mr[t], self)) {
						mr[t] = s; ml[s] = t;
						return true;
					}
				} else d[t] = min(d[t], diff);
			}
			return false;
		};
		for(size_t i=0;i<n;i++) {
			if(ml[i] != NONE) continue;
			d.assign(n, numeric_limits<double>::max());
			while(true) {
				S.assign(n, 0); T.assign(n, 0);
				if(kuhn(i,kuhn)) break;
				double delta = numeric_limits<double>::max();
				for(size_t j=0;j<n;j++) if(!T[j]) delta=min(delta, d[j]);
				for(size_t s=0;s<n;s++) if(S[s]) y[s] -= delta;
				for(size_t j=0;j<n;j++) {
					if(T[j]) z[j] += delta;
					else d[j] -= delta;
				}
			}
		}
		double ret = 0;
		for(size_t i=0;i<n;i++) ret += y[i];
		for(size_t j=0;j<n;j++) ret += z[j];
		return MAXIMIZE?ret:-ret;
	}
};
