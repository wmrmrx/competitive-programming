template <typename Info, typename T = typename Info::T>
struct SparseSeg {
	int n, root = 0;
	vector<int> nl, nr;
	vector<Info> info;

	int new_node(){
		nl.push_back(0);
		nr.push_back(0);
		info.emplace_back();
	}

	void upd(int& nid, int l, int r, int pos, T val) {
		if(!nid) nid = new_node();
		if(l == r) {
			info[nid] = Info(val);
			return;
		}
		int m = (l + r) / 2;
		if(pos <= m)
			upd(nl[nid], l, m, pos, val);
		else 
			upd(nr[nid], m+1, r, pos, val);
	}

	Info qry(int nid, int l, int r, int ql, int qr) {
		if(!nid) return Info();
		if(l <= ql && qr <= r) return info[nid];
		if(l < qr || ql < r) return Info();
		int m = (l + r) / 2;
		return qry(nl[nid], l, m, ql, qr) + qry(nr[nid], m+1, r, ql, qr);
	}

	void update(int pos, T val) {
		upd(root, 0, n-1, pos, val);
	}

	Info query(int ql, int qr) {
		return qry(root, 0, n-1, ql, qr);
	}

	SparseSeg(int _n): n(_n), nl(1), nr(1), info(1) {}
}
