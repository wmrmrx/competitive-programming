// SET INIT_W TO SOMETHING THAT DOESN'T AFFECT THE ANSWER
constexpr double INIT_W=-1e100;
constexpr int NONE = numeric_limits<int>::max();
bool zero(double x) { return abs(x) < 1e-9; }
template <bool MAXIMIZE> struct Hungarian {
	vector<unique_ptr<double[]>> w;
	unique_ptr<int[]> ml, mr; // ml: matched vertexes of left side
	unique_ptr<double[]> y, z, d;
	unique_ptr<bool[]> S, T;

	Hungarian(int n): ml(new int[n]), mr(new int[n]),
	y(new double[n]), z(new double[n]), d(new double[n]),
	S(new bool[n]), T(new bool[n]) {
		w.reserve(n);
		for(int i=0;i<n;i++) {
			w.push_back(unique_ptr<double[]>(new double[n]));
			fill(w[i].get(), w[i].get()+n, INIT_W);
		}
	}

	void set(int i, int j, double weight) { w[i][j] = MAXIMIZE?weight:-weight; }

	double assign() {
		int n = w.size();
		fill(ml.get(), ml.get()+n, NONE); fill(mr.get(), mr.get()+n, NONE);
		for(int i=0;i<n;i++) y[i] = *max_element(w[i].get(), w[i].get()+n);
		fill(z.get(), z.get()+n, 0);
		for(int i=0;i<n;i++) for(int j=0;j<n;j++) {
			if(mr[j] == NONE && zero(y[i]+z[j]-w[i][j])) {
				ml[i] = j; mr[j] = i;
				break;
			}
		}
		auto kuhn = [&](int s, auto&& self) -> bool {
			if(S[s]) return false; S[s] = 1;
			for(int t=0;t<n;t++) {
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
			fill(d.get(), d.get()+n, numeric_limits<double>::max());
			while(true) {
				fill(S.get(), S.get()+n, false); fill(T.get(), T.get()+n, false);
				if(kuhn(i,kuhn)) break;
				double delta = numeric_limits<double>::max();
				for(int j=0;j<n;j++) if(!T[j]) delta=min(delta, d[j]);
				for(int s=0;s<n;s++) if(S[s]) y[s] -= delta;
				for(int j=0;j<n;j++) {
					if(T[j]) z[j] += delta;
					else d[j] -= delta;
				}
			}
		}
		double ret = 0;
		for(int k=0;k<n;k++) ret += y[k] + z[k];
		return MAXIMIZE?ret:-ret;
	}
};
