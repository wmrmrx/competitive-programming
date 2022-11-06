namespace nt {
	constexpr int MAX = 300'000;
	// div[i]: smallest prime that divides i
	int div[MAX];

	// primes: list of primes between 2 and MAX
	vector<int> primes;

	void init() {
		for(int i=2;i<MAX;i++) if(!div[i]) {
			div[i] = i;
			primes.push_back(i);
			for(int j=i*i;j<MAX;j+=i) if(!div[j])
				div[j] = i;
		}
	}

	bool is_prime(int x) {
		if(x < MAX) return div[x] == x;
		for(int p: primes) {
			if(p*p > x) break;
			if(x%p == 0) return false;
		}
		return true;
	}

	map<int,int> factorize(int x) {
		map<int,int> f;
		if(x < MAX) {
			while(int p = div[x]) {
				f[p]++;
				x /= p;
			}
		} else {
			for(int p: primes) {
				if(p*p > x) break;
				while(x%p == 0) {
					x /= p;
					f[p]++;
				}
			}
			if(x > 1) f[x] = 1;
		}
		return f;
	}
}
