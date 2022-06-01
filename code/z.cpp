template <typename T> vector<int> z_alg(int sz, T s[]) {
	vector<int> ret(sz);
	for(int l=0,r=0,i=1;i<sz;i++) {
		if(i >= r) {
			l=r=i;
			while(r<sz && s[r-l]==s[r]) r++;
			ret[i] = r-l;
		} else {
			if((int)ret[i-l] < r-i) ret[i] = ret[i-l];
			else {
				l=i;
				while(r<sz && s[r-l]==s[r]) r++;
				ret[i] = r-l;
			}
		}
	}
	return ret;
}
