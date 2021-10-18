template <typename T> struct RMQ {
	vector<vector<T>> dp;
	RMQ<T>(T v[], long long n) {
		long long log = 63-__builtin_clzll(n);
		dp = vector<vector<T>>(n+1,vector<T>(log+1));
		for(int i=1;i<=n;i++) {
			dp[i][0] = v[i];
		}
		for(int l=1;l<=log;l++) {
			for(int i=1;i<=n;i++) {
				int other = i + (1<<(l-1));
				if(other > n) {
					other = n;
				}
				dp[i][l] = min(dp[i][l-1],dp[other][l-1]);
			}
		}
	}
	T query(long long a, long long b) {
		if(a == b) {
			return dp[a][0];
		}
		long long diff = b-a;
		int pot = 63-__builtin_clzll(diff);
		return min( dp[a][pot] , dp[b-(1<<pot)+1][pot] );
	}
};
