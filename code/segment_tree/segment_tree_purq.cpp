template <typename Info, typename T = typename Info::T> 
class SegPURQ {
private: 
	int size;
	vector<Info> info;

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

	Info query(int nid, const int l, const int r, const int ql, const int qr) const {
		if(qr < l || r < ql) return Info();
		if(ql <= l && r <= qr) { return info[nid]; };
		const int m = (l + r)/2;
		return query(nid + 1, l, m, ql, qr) + query(nid + 2*(m - l + 1), m+1, r, ql, qr);
	}

	void update(int nid, const int l, const int r, const int pos, const T& val) {
		if(r < pos || pos < l) return;
		if(l == r) { 
			info[nid] = Info(val);
			return; 
		}
		const int m = (l + r)/2;
		update(nid + 1, l, m, pos, val); 
		update(nid + 2*(m - l + 1), m+1, r, pos, val);
		info[nid] = info[nid + 1] + info[nid + 2*(m - l + 1)];
	}
public:
	SegPURQ(const vector<T>& v): size(v.size()) {
		info.resize(2*size - 1);
		build(0, 0, size-1, v);
	}

	SegPURQ(int _size): size(_size) {
		info.resize(2*size - 1);
	}

	Info query(const int ql, const int qr) const {
		assert(0 <= ql && ql <= qr && qr < size);
		return query(0, 0, size-1, ql, qr);
	}

	void update(const int pos, const T& val) {
		assert(0 <= pos && pos < size);
		update(0, 0, size-1, pos, val);
	}
};
