vector<int> compress(vector<int> &arr) {
	set<int> comp_set;
	for(int i: arr) {
		comp_set.insert(i);
	}
	vector<int> ret(comp_set.size());
	map<int,int> comp_mp;
	int cnt = 0;
	for(int i: comp_set) {
		comp_mp[i] = cnt;
		ret[cnt] = i;
		cnt++;
	}
	for(int &x: arr) {
		x = comp_mp[x];
	}
	return ret;
}
