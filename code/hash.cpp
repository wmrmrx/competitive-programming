template <typename T, uint64_t PRIME=1000000007, uint64_t MOD=10007> struct Hash {
	const size_t size;
	const T* s;
	vector<uint64_t> pot, h;
	Hash(size_t size, const T s[]): size(size), s(s) {
		pot.assign(size, 1);
		for(size_t i=1;i<size;i++) pot[i] = pot[i-1]*PRIME%MOD;
		h.assign(size, 0);
		for(size_t i=0;i<size;i++) h[i] = uint64_t(s[i])*pot[size-1-i]%MOD;
		for(size_t i=1;i<size;i++) h[i] = (h[i]+h[i-1])%MOD;
	};
	uint64_t get(size_t a, size_t b) {
		return (MOD+h[b]-(a?h[a-1]:0))*pot[a]%MOD;
	}
};
