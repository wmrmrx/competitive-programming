template <typename T> vector<int> z_alg(size_t size, T s[]) {
	vector<int> ret(size);
	ret[0] = size;
	size_t l = 0, r = 0;
	for(size_t i=1;i<size;i++) {
		if(i >= r) {
			l=r=i;
			while(r<size && s[r-l]==s[r]) {
				r++;
			}
			ret[i] = r-l;
		} else {
			size_t k = i-l;
			if((size_t)ret[k] < r-i) {
				ret[i] = ret[k];
			} else {
				l=i;
				while(r<size && s[r-l]==s[r]) {
					r++;
				}
				ret[i] = r-l;
			}
		}
	}
	return ret;
}
