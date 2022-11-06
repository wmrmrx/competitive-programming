namespace ntt {
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
			if(x%p == 0) {
				return false;
			}
		}
		return true;
	}

	map<int,int> factorize(int n) {
		map<int,int> f;
		if(n >= MAX) {
			for(int p: primes) {
				if(p*p > n) break;
				while(n%p == 0) {
					n /= p;
					f[p]++;
				}
			}
			if(n > 1) f[n] = 1;
		} else {
			while(int p = div[n]) {
				f[p]++;
				n /= p;
			}
		}
		return f;
	}
}
