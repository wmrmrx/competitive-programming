constexpr size_t NONE = numeric_limits<size_t>::max();
bool zero(int64_t x) { return x == 0; }
template <bool MAXIMIZE=false> struct Hungarian {
	vector<vector<int64_t>> w;
	vector<size_t> ml, mr; // ml: matched vertexes of left side
	vector<int64_t> y, z, d;
	vector<bool> S, T;
	Hungarian(size_t n): w(n,vector<int64_t>(n)),ml(n),mr(n),y(n),z(n),d(n),S(n),T(n) {}
	void set(size_t i, size_t j, int64_t weight) { w[i][j] = MAXIMIZE?weight:-weight; }
	int64_t assign() {
		size_t n = w.size();
		ml.assign(n, 0); mr.assign(n, 0);
		for(size_t i=0;i<n;i++) y[i] = *max_element(w[i].begin(), w[i].end());
		z.assign(n, 0);
		auto kuhn = [&](size_t s, auto&& self) -> bool {
			if(S[s]) return false; S[s] = 1;
			for(size_t t=0;t<n;t++) {
				int64_t diff = y[s]+z[t]-w[s][t];
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
			d.assign(numeric_limits<int64_t>::max(), n);
			while(true) {
				S.assign(0, n); T.assign(0, n);
				if(kuhn(i,kuhn)) break;
				int64_t delta = numeric_limits<int64_t>::max();
				for(size_t j=0;j<n;j++) if(!T[j]) delta=min(delta, d[j]);
				for(size_t s=0;s<n;s++) if(S[s]) y[s] -= delta;
				for(size_t j=0;j<n;j++) {
					if(T[j]) z[j] += delta;
					else d[j] -= delta;
				}
			}
		}
		int64_t ret = 0;
		for(size_t i=0;i<n;i++) ret += y[i];
		for(size_t j=0;j<n;j++) ret += z[j];
		return MAXIMIZE?ret:-ret;
	}
};
