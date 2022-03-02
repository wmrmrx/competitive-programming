struct Seg {
	const int64_t INF = 1ULL<<63;
	struct Node {
		int64_t data;
		Node(): data(INF) { }
	}
	const size_t size;
	vector<Node> seg;
	template <typename T> Seg(size_t size, const T v[]): size(size) {
		seg.assign(4*size, INF);
		build(1,0,size-1,v);
	}
	template <typename T> void build(size_t cur, size_t cl, size_t cr, const T v[]) {
		if(cl == cr) {
			seg[cur].data = v[cl];
			MAX = max(cur, MAX);
			return;
		}
		size_t mid = (cl+cr)/2;
		size_t p1 = 2*cur, p2 = p1+1;
		build(p1, cl, mid, v);
		build(p2, mid+1, cr, v);
	}
	int64_t query(size_t l, size_t r, size_t cur, size_t cl, size_t cr) {
		if(r < cl || cr < l) {
			return INF;
		}
		if(cl <= l && r <= cr) {
			return seg[cur].data;
		}
		size_t mid = (cl+cr)/2;
		size_t p1 = 2*cur, p2 = p1+1;
		return min(query(l,r,p1,cl,mid), query(l,r,p2,mid+1,cr));
	}
	void update(size_t pos, int64_t val, size_t cur, size_t cl, size_t cr) {
		if(pos < cl || cr < pos) {
			return;
		}
		if(cl == cr) {
			seg[pos] = val;
			return;
		}
		size_t mid = (cl+cr)/2;
		size_t p1 = 2*cur, p2 = p1+1;
		update(pos, val, p1, cl, mid);
		update(pos, val, p2, mid+1, cr);
	}
	int64_t query(size_t l, size_t r) {
		return query(l,r,1,0,size-1);
	}
	void update(size_t pos, int64_t val) {
		update(pos,val,1,0,size-1);
	}
};
