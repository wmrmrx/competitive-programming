vector<int> sieve(int n) {
	vector<bool> crivo(n+1);
	vector<int> primos;
	for(int i=2;i<=n;i++) {
		if(crivo[i]) {
			continue;
		}
		primos.push_back(i);
		for(int j=i*i;j<=n;j+=i) {
			crivo[j] = true;
		}
	}
	return primos;
}
