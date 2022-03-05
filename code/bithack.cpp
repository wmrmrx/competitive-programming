// iterator through all masks with n bits and m set bits
struct BitIterator {
	const uint32_t n, m;
	uint32_t cur;
	BitIterator(const uint32_t n, const uint32_t m): n(n), m(m) {}
	BitIterator(const uint32_t n, const uint32_t m, const uint32_t cur): n(n), m(m), cur(cur) {}
	void operator++(){const uint32_t t=cur|(cur-1);cur=(t+1)|(((~t&-~t)-1)>>__builtin_ffs(cur));}
	uint32_t operator*() const { return cur; }
	bool operator!=(const BitIterator& other) const { return cur < other.cur; };
	BitIterator begin() const { return BitIterator(n, m, (1<<m)-1); }
	BitIterator end() const { return BitIterator(n, m, (1<<n)); }
};
