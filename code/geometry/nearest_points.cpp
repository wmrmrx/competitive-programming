i64 nearest_points(vector<point> v) {
	using lim = numeric_limits<i64>;
	i64 res = lim::max(), sq = sqrt((double)res+1);
	sort(all(v));
	for(int i=1;i<v.size();i++) if(v[i] == v[i-1]) return 0;
	auto by_y = [](const point& a, const point& b) {
		using tup = tuple<i64, i64>;
		return tup{a.y, a.x} < tup{b.y, b.x};
	};
	queue<point> active;
	set<point, decltype(by_y)> pts(by_y);
	for(auto& p: v) {
		while(!active.empty() && p.x-active.front().x > sq) {
			pts.erase(active.front());
			active.pop();
		}
		auto it = pts.lower_bound({lim::min(), p.y-sq});
		while(it != pts.end() && it->y <= p.y + sq) {
			int d = dist2(p, *it);
			if(d < res) {
				res = d;
				sq = sqrt((double)res+1);
			}
			it++;
		}
		active.push(p);
		pts.insert(p);
	}
	return res;
}
