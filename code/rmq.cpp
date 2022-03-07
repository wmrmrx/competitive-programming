template <typename T, bool MaxQuery = false> struct RMQ {
	const vector<vector<T>> dp;
	T min_or_max(const T a, const T b) const { return MaxQuery ? max<T>(a,b) : min<T>(a,b); }
	vector<vector<T>> build(const size_t size, const T v[]) {
		const size_t log = 63-__builtin_clzll(size);
		vector<vector<T>> ret(log+1, vector<T>(size));
		for(size_t i=0;i<size;i++)ret[0][i]=v[i];
		for(size_t l=1;l<=log;l++) for(size_t i=0;i<size;i++) 
			ret[l][i] = min_or_max(ret[l-1][i],ret[l-1][min(i+(1<<(l-1)), size)]);
		return ret;
	}
	RMQ(const size_t size, const T v[]): dp(build(size,v)) {}
	T query(size_t a, size_t b) const {
		if(a == b) return dp[0][a];
		size_t pot = 63-__builtin_clzll(b-a);
		return min_or_max(dp[pot][a], dp[pot][b-(1<<pot)+1]);
	}
};
