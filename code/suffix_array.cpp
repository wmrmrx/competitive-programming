struct SuffixArray {
	vector<int> v, inv, lcp;

	template <typename T>
	SuffixArray(int sz, const T s[]): v(sz+1), inv(sz+1), lcp(sz) {
		iota(v.begin()+1, v.end(), 0);
		sort(v.begin()+1, v.end(), [&](int i, int j) { return s[i] < s[j]; });
		v[0] = sz++;
		vector<int> ra(sz), newra(sz), newv(sz), cnt(sz+1);
		ra[v[1]] = 1;
		for(int i=2;i<sz;i++) ra[v[i]] = ra[v[i-1]] + (s[v[i]] != s[v[i-1]]);
		for(int k=1;k<sz;k*=2) {
			for(int i=0;i<sz;i++) v[i] = (v[i]-k+sz)%sz;
			fill(all(cnt), 0);
			for(int x: ra) cnt[x+1]++;
			partial_sum(all(cnt), cnt.begin());
			for(int i=0;i<sz;i++) newv[cnt[ra[v[i]]]++] = v[i];
			v.swap(newv);
			for(int i=1;i<sz;i++) {
				int diff = ra[v[i]] != ra[v[i-1]] || ra[(v[i]+k)%sz] != ra[(v[i-1]+k)%sz];
				newra[v[i]] = newra[v[i-1]] + diff;
			}
			ra.swap(newra);
		}
		for(int i=0;i<sz;i++) inv[v[i]] = i;
		for(int l=0,i=0;i<sz-1;i++) {
			int j = v[inv[i]-1];
			while(max(i,j)+l<sz-1 && s[i+l] == s[j+l]) l++;
			lcp[inv[i]-1] = l;
			if(l) l--;
		}
	}
};
