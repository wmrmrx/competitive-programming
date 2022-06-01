template <typename T, int PRIME=10007> struct Hash {
	vector<Z> pot, h;
	Hash(int sz, T s[]): pot(sz), h(sz) {
		pot[0] = Z(1);
		for(int i=1;i<sz;i++) pot[i] = pot[i-1]*Z(PRIME);
		for(int i=0;i<sz;i++) h[i] = Z(s[i])*pot[sz-1-i];
		for(int i=1;i<sz;i++) h[i] += h[i-1];
	}
	Z get(int a, int b) {
		return (h[b]-(a?h[a-1]:Z(0)))*pot[a];
	}
};
