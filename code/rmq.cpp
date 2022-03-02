template <typename T, bool MaxQuery = false> struct RMQ {
	vector<vector<T>> dp;
	inline T min_or_max(const T a, const T b) {
		return MaxQuery ? max(a,b) : min(a,b);
	}
	RMQ<T>(size_t size, const T v[]) {
		size_t log = 63-__builtin_clzll(size);
		dp.assign(log+1, vector<T>(size));
		for(size_t i=0;i<size;i++) {
			dp[0][i] = v[i];
		}
		for(size_t l=1;l<=log;l++) {
			for(size_t i=0;i<size;i++) {
				size_t other = min(i+(1<<(l-1)), size);
				dp[l][i] = min_or_max(dp[l-1][i],dp[l-1][other]);
			}
		}
	}
	T query(size_t a, size_t b) {
		assert(a <= b);
		assert(b < dp[0].size());
		if(a == b) {
			return dp[0][a];
		}
		size_t diff = b-a;
		size_t pot = 63-__builtin_clzll(diff);
		return min_or_max(dp[pot][a], dp[pot][b-(1<<pot)+1]);
	}
};
