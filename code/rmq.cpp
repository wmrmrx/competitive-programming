// ONE INDEXED
template <typename T> struct RMQ {
	vector<vector<T>> dp;
	RMQ<T>(size_t size, const T v[]) {
		size_t log = 63-__builtin_clzll(size);
		dp.assign(size, vector<T>(log+1));
		for(size_t i=1;i<=size;i++) {
			dp[i][0] = v[i];
		}
		for(size_t l=1;l<=log;l++) {
			for(size_t i=1;i<=n;i++) {
				size_t other = min(i+(1<<(l-1)), size);
				if(other > n) {
					other = n;
				}
				dp[i][l] = min(dp[i][l-1],dp[other][l-1]);
			}
		}
	}
	T query(size_t a, size_t b) {
		assert(a <= b);
		if(a == b) {
			return dp[a][0];
		}
		size_t diff = b-a;
		size_t pot = 63-__builtin_clzll(diff);
		return min( dp[a][pot] , dp[b-(1<<pot)+1][pot] );
	}
};
