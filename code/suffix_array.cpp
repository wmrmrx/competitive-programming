struct SuffixArray {
	vector<int> p, lcp;

	template <typename T>
	SuffixArray(int sz, const T s[]): p(sz+1), lcp(sz+2) {
		iota(p.begin()+1, p.end(), 0);
		sort(p.begin()+1, p.end(), [&](int i, int j) { return s[i] < s[j]; });
		p[0] = sz++;
		vector<int> ra(sz), newra(sz), newp(sz), cnt(sz+2);
		ra[p[1]] = 1;
		for(int i=2;i<sz;i++) ra[p[i]] = ra[p[i-1]] + (s[p[i]] != s[p[i-1]]);
		for(int k=1;k<sz;k*=2) {
			for(int i=0;i<sz;i++) p[i] = (p[i]-k+sz)%sz;
			fill(cnt.begin(), cnt.end(), 0);
			for(int x: ra) cnt[x+1]++;
			partial_sum(cnt.begin(), cnt.end(), cnt.begin());
			for(int i=0;i<sz;i++) newp[cnt[ra[p[i]]]++] = p[i];
			p.swap(newp);
			for(int i=1;i<sz;i++) {
				int diff = ra[p[i]] != ra[p[i-1]] || ra[(p[i]+k)%sz] != ra[(p[i-1]+k)%sz];
				newra[p[i]] = newra[p[i-1]] + diff;
			}
			ra.swap(newra);
		}
	}
};
