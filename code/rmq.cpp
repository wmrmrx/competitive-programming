template <typename T, bool MaxQuery = false> struct RMQ {
	vector<vector<T>> dp;
	T min_or_max(const T a, const T b) const { return MaxQuery ? max<T>(a,b) : min<T>(a,b); }
	RMQ(size_t size, const T v[]) {
		size_t log = 63-__builtin_clzll(size);
		dp.assign(log+1, vector<T>(size));
		for(size_t i=0;i<size;i++)dp[0][i]=v[i];
		for(size_t l=1;l<=log;l++) for(size_t i=0;i<size;i++) 
			dp[l][i] = min_or_max(dp[l-1][i],dp[l-1][min(i+(1<<(l-1)), size)]);
	}
	T query(size_t a, size_t b) const {
		if(a == b) return dp[0][a];
		size_t pot = 63-__builtin_clzll(b-a);
		return min_or_max(dp[pot][a], dp[pot][b-(1<<pot)+1]);
	}
};
