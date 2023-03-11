template <typename D, typename T=typename D::T> 
class SegPURQ {
private: 
	int size;
	vector<D> data;

	void build(int nid, const int l, const int r, const vector<T>& v) {
		if(l == r) {
			data[nid] = D(v[l]);
			return;
		}
		const int m = (l + r)/2;
		build(nid + 1, l, m, v);
		build(nid + 2*(m - l + 1), m+1, r, v);
		data[nid] = data[nid + 1] + data[nid + 2*(m - l + 1)];
	}

	D query(int nid, const int l, const int r, const int ql, const int qr) const {
		if(qr < l || r < ql) return D();
		if(ql <= l && r <= qr) { return data[nid]; };
		const int m = (l + r)/2;
		return query(nid + 1, l, m, ql, qr) + query(nid + 2*(m - l + 1), m+1, r, ql, qr);
	}

	void update(int nid, const int l, const int r, const int pos, const T& val) {
		if(r < pos || pos < l) return;
		if(l == r) { 
			data[nid] = D(val); 
			return; 
		}
		const int m = (l + r)/2;
		update(nid + 1, l, m, pos, val); 
		update(nid + 2*(m - l + 1), m+1, r, pos, val);
		data[nid] = data[nid + 1] + data[nid + 2*(m - l + 1)];
	}
public:
	SegPurq(const vector<T>& v): size(v.size()) {
		data.resize(2*size - 1);
		build(0, 0, size-1, v);
	}

	SegPurq(int _size): size(_size) {
		data.resize(2*size - 1);
	}

	D query(const int ql, const int qr) const {
		assert(0 <= ql && ql <= qr && qr < size);
		return query(0, 0, size-1, ql, qr);
	}

	void update(const int pos, const T& val) {
		assert(0 <= pos && pos < size);
		update(0, 0, size-1, pos, val);
	}
};

struct Data {
	using T = int;
	int x;

	Data(): x(numeric_limits<T>::max()) {}
	Data(T _x): x(_x) {}

	friend Data operator+(const Data lhs, const Data rhs) {
		Data res;
		res.x = min(lhs.x, rhs.x);
		return res;
	}
};
