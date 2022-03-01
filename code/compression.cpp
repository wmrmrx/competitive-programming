vector<int> compress(vector<int> &arr) {
	set<int> comp_set;
	for(int i: arr) {
		comp_set.insert(i);
	}
	vector<int> ret(comp_set.size());
	map<int,uint32_t> comp_mp;
	uint32_t cnt = 0;
	for(int i: comp_set) {
		comp_mp[i] = cnt;
		ret[cnt] = i;
		cnt++;
	}
	for(int& x: arr) {
		x = comp_mp[x];
	}
	return ret;
}
