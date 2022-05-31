// SET INIT_W TO SOMETHING THAT DOESN'T AFFECT THE ANSWER
constexpr double INIT_W=-1e100;
constexpr int NONE = numeric_limits<int>::max();
bool zero(double x) { return abs(x) < 1e-9; }
template <bool MAXIMIZE> struct Hungarian {
	int n, m;
	unique_ptr<unique_ptr<double[]>[]> w;
	unique_ptr<int[]> ml, mr; // ml: matched vertexes of left side
	unique_ptr<double[]> y, z, d;
	unique_ptr<bool[]> S, T;

	Hungarian(int n, int m): n(n), m(m), 
	ml(new int[n]), mr(new int[m]),
	y(new double[n]), z(new double[m]), d(new double[m]),
	S(new bool[n]), T(new bool[m]) {
		w.reset(new unique_ptr<double[]>[n]);
		for(int i=0;i<n;i++) {
			w[i].reset(new double[m]);
			fill_n(w[i].get(), m, INIT_W);
		}
	}

	void set(int i, int j, double weight) { w[i][j] = MAXIMIZE?weight:-weight; }

	double assign() {
		fill_n(ml.get(), n, NONE); fill_n(mr.get(), m, NONE);
		for(int i=0;i<n;i++) y[i] = *max_element(w[i].get(), w[i].get()+m);
		fill_n(z.get(), m, 0);
		for(int i=0;i<n;i++) for(int j=0;j<m;j++) {
			if(mr[j] == NONE && zero(y[i]+z[j]-w[i][j])) {
				ml[i] = j; mr[j] = i;
				break;
			}
		}
		auto kuhn = [&](int s, auto&& self) -> bool {
			if(S[s]) return false; S[s] = 1;
			for(int t=0;t<m;t++) {
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
		for(int i=0;i<n;i++) {
			if(ml[i] != NONE) continue;
			fill_n(d.get(), m, numeric_limits<double>::max());
			while(true) {
				fill_n(S.get(), n, false); fill_n(T.get(), m, false);
				if(kuhn(i,kuhn)) break;
				double delta = numeric_limits<double>::max();
				for(int j=0;j<m;j++) if(!T[j]) delta=min(delta, d[j]);
				for(int s=0;s<n;s++) if(S[s]) y[s] -= delta;
				for(int j=0;j<m;j++) {
					if(T[j]) z[j] += delta;
					else d[j] -= delta;
				}
			}
		}
		double res = 0;
		for(int i=0;i<n;i++) res += y[i];
		for(int j=0;j<m;j++) res += z[j];
		return MAXIMIZE?res:-res;
	}
};
