vector<int> mobius(size_t size) {
	// u(n) =  1 if n is square-free with an even number of prime factors
	//        -1 if n is square-free with an odd number of prime factors
	//         0 if n has a squared prime factor
	// f(n) = Σ(g(d)) for d|n => g(n) = Σ(u(d)g(n/d)) for d|n
	// Σ(u(d)) for d|n = [n == 1]
	vector<int> ret(size+1),marc(size+1),div(size+1);
	ret[1] = 1;
	for(size_t i=2;i<=size;i++) {
		if(marc[i]) continue;
		ret[i] = -1;
		for(size_t j=i*i;j<=size;j+=i) {
			if(marc[j]) continue;
			marc[j] = 1;
			div[j] = i;
		}
	}
	for(size_t i=2;i<=size;i++) {
		if(!marc[i]) continue;
		size_t d = i/div[i];
		if(d%div[i] == 0) ret[i] = 0;
		else ret[i] = ret[d] * ret[i/d];
	}
	return ret;
}
