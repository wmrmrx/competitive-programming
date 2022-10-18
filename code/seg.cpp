struct Seg {
	struct data {
		int mn, mx, sum;

		data() {}
		data(int val): mn(val), mx(val), sum(val) {}

		static data nil() {
			using lim = numeric_limits<int>;
			return data{lim::max(), lim::min(), 0};
		}

		data merge(data rhs) {
			return data{min(mn,rhs.mn),max(mx,rhs.mx),sum+rhs.sum};
		}
	};

	struct node {
		node *l, *r;
		data d;

		node(): l(0), r(0), d() {}
		node(data d): l(0), r(0), d(d) {}
	};

	int sz;
	vector<node> arena;

	node* new_node(data d = data::nil()) {
		arena.push_back(node(d));
		return &arena.back();
	}

	Seg(int sz): sz(sz) {
		arena.reserve(2*sz-1);
		new_node();
		build(arena[0],0,sz-1);
	}

	void build(node& cur, int cl, int cr) {
		if(cl == cr) return; 
		int mid = (cl+cr)/2;
		cur.l = new_node(); cur.r = new_node();
		build(*cur.l, cl, mid);
		build(*cur.r, mid+1, cr);
	}

	data query(node& cur, int cl, int cr, int ql, int qr) {
		if(qr < cl || cr < ql) return data::nil();
		if(ql <= cl && cr <= qr) return cur.d;
		int mid = (cl+cr)/2;
		return query(*cur.l, cl, mid, ql, qr)
			.merge(query(*cur.r, mid+1, cr, ql, qr));
	}

	data query(int ql, int qr) {
		return query(arena[0], 0, sz-1, ql, qr);
	}

	void update(node& cur, int cl, int cr, int pos, int val) {
		if(pos < cl || cr < pos) return;
		if(cl == cr) {
			cur.d = data(val);
			return; 
		}
		int mid = (cl+cr)/2;
		update(*cur.l, cl, mid, pos, val);
		update(*cur.r, mid+1, cr, pos, val);
		cur.d = cur.l->d.merge(cur.r->d);
	}

	void update(int pos, int val) {
		return update(arena[0], 0, sz-1, pos, val);
	}
};
