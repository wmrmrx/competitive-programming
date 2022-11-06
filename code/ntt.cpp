namespace ntt {
	constexpr size_t MAX = 300'000;
	// div[i]: smallest prime that divides i
	int div[MAX];

	// primes: list of primes between 2 and MAX
	vector<int> primes;

	void crivo() {
		for(int i=2;i<MAX;i++) if(!div[i]) {
			div[i] = i;
			primes.push_back(i);
			for(int j=i*i;j<MAX;j+=i)
				div[j] = div[j] ? i : min(div[j], i);
		}
	}

	bool is_prime(int x) {
		return div[x] == x;
	}

	map<int,int> factorize(int n) {
		map<int,int> f;
		if(n >= MAX) {
			for(int p: primes) {
				if(p*p >= n) break;
				while(n%p == 0) {
					n /= p;
					f[p]++;
				}
			}
		} else {
			while(int p = div[n]) {
				f[p]++;
				n /= p;
			}
		}
		return f;
	}
	
	void init() {
		crivo();
	}
}
