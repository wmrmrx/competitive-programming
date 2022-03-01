template <typename Iterator> vector<int> compress(Iterator begin, Iterator end) {
	set<int> comp_set;
	for(auto it = begin; it != end; it++) {
		comp_set.insert(*it);
	}
	vector<int> ret(comp_set.size());
	map<int,uint32_t> comp_mp;
	uint32_t cnt = 0;
	for(int i: comp_set) {
		comp_mp[i] = cnt;
		ret[cnt] = i;
		cnt++;
	}
	for(auto it = begin; it != end; it++) {
		*it = comp_mp[*it];
	}
	return ret;
}
