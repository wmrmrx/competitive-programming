vector<int> sieve(int n) {
	vector<bool> marc(n+1);
	vector<int> primes;
	for(int i=2;i<=n;i++) {
		if(marc[i]) {
			continue;
		}
		primes.push_back(i);
		for(int j=i*i;j<=n;j+=i) {
			marc[j] = true;
		}
	}
	return primes;
}
