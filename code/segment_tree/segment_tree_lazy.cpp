template <typename Info, typename T = typename Info::T, typename U = typename Info::U, typename Tag = typename Info::Tag> 
class SegLazy {
private: 
	int size;
	vector<Info> info;
	vector<Tag> tag;

	void build(int nid, const int l, const int r, const vector<T>& v) {
		if(l == r) {
			info[nid] = Info(v[l]);
			return;
		}
		const int m = (l + r)/2;
		build(nid + 1, l, m, v);
		build(nid + 2*(m - l + 1), m+1, r, v);
		info[nid] = info[nid + 1] + info[nid + 2*(m - l + 1)];
	}

	void push(const int nid, const int l, const int r) {
		tag[nid].apply(info[nid], l, r);
		if(l != r) {
			const int m = (l + r)/2, x = nid + 1, y = nid + 2*(m - l + 1);
			tag[x] += tag[nid];
			tag[y] += tag[nid];
		}
		tag[nid] = Tag();
	}

	Info query(const int nid, const int l, const int r, const int ql, const int qr) {
		push(nid, l, r);
		if(qr < l || r < ql) return Info();
		if(ql <= l && r <= qr) { return info[nid]; };
		const int m = (l + r)/2, x = nid + 1, y = nid + 2*(m - l + 1);
		return query(x, l, m, ql, qr) + query(y, m+1, r, ql, qr);
	}

	void update(const int nid, const int l, const int r, const int ql, const int qr, const U& val) {
		push(nid, l, r);
		if(qr < l || r < ql) return;
		if(ql <= l && r <= qr) { 
			tag[nid] += Tag(val);
			push(nid, l, r);
			return; 
		}
		const int m = (l + r)/2, x = nid + 1, y = nid + 2*(m - l + 1);
		update(x, l, m, ql, qr, val); 
		update(y, m+1, r, ql, qr, val);
		info[nid] = info[x] + info[y];
	}
public:
	SegLazy(const vector<T>& v): size(v.size()), info(2*size-1), tag(2*size-1) {
		build(0, 0, size-1, v);
	}

	SegLazy(int _size): size(_size), info(2*size - 1), tag(2*size - 1) {}

	Info query(const int ql, const int qr) {
		assert(0 <= ql && ql <= qr && qr < size);
		return query(0, 0, size-1, ql, qr);
	}

	void update(const int ql, const int qr, const U& val) {
		assert(0 <= ql && ql <= qr && qr < size);
		update(0, 0, size-1, ql, qr, val);
	}
};
