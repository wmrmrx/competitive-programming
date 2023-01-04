struct Data {
	using B = int;
	int x;

	Data(): x(numeric_limits<int>::max()) {}
	Data(B _x): x(_x) {}

	friend Data operator+(const Data lhs, const Data rhs) {
		Data res;
		res.x = min(lhs.x, rhs.x);
		return res;
	}
};

template <typename D, bool SUBSTITUTION=false, typename U=typename D::B> 
class Seg {
private: 
	struct node {
		node *l, *r;
		D data;
		node(node* _l=0, node *_r=0, D _data=D()): l(_l), r(_r), data(_data) {}
	};

	int sz;
	vector<node> arena;

	void build(node& cur, const int cl, const int cr, const U* v) {
		if(cl == cr) {
			if(v) cur.data = D(v[cl]);
			return;
		}
		const int m = (cl + cr)/2;
		arena.push_back(node()); cur.l = &arena.back();
		build(*cur.l, cl, m, v);
		arena.push_back(node()); cur.r = &arena.back();
		build(*cur.r, m+1, cr, v);
		cur.data = cur.l->data + cur.r->data;
	}

	D query(const node& cur, const int cl, const int cr, const int ql, const int qr) const {
		if(qr < cl || cr < ql) return D();
		if(ql <= cl && cr <= qr) { return cur.data; };
		const int m = (cl + cr)/2;
		return query(*cur.l, cl, m, ql, qr) + query(*cur.r, m+1, cr, ql, qr);
	}

	void update(node& cur, const int cl, const int cr, const int pos, const U& val) {
		if(cr < pos || pos < cl) return;
		if(cl == cr) { 
			if constexpr(SUBSTITUTION) cur.data = D(val); 
			else cur.data = cur.data + D(val); 
			return; 
		}
		const int m = (cl + cr)/2;
		update(*cur.l, cl, m, pos, val); update(*cur.r, m+1, cr, pos, val);
		cur.data = cur.l->data + cur.r->data;
	}
public:
	Seg(const vector<U>& v): sz(v.size()) {
		arena.reserve(2*sz-1);
		arena.push_back(node());
		build(arena[0], 0, sz-1, v.data());
	}

	Seg(int _sz): sz(_sz) {
		arena.reserve(2*sz-1);
		arena.push_back(node());
		build(arena[0], 0, sz-1, nullptr);
	}

	D query(const int ql, const int qr) const {
		return query(arena[0], 0, sz-1, ql, qr);
	}

	void update(const int pos, const U& val) {
		update(arena[0], 0, sz-1, pos, val);
	}
};
