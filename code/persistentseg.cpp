struct PersistentSeg {
	struct Node {
		size_t lchild, rchild;
		int64_t data;
		Node(): lchild(0), rchild(0), data(0) {}
	};
	const size_t size;
	vector<Node> nodes;
	vector<size_t> roots;
	PersistentSeg(size_t size): size(size) {
		nodes.reserve(size*(1<<20));
		roots.push_back(new_node());
		build(nodes[0],0,size-1);
	}
	size_t new_node() {
		nodes.push_back(Node());
		return nodes.size()-1;
	}
	void build(Node& cur, size_t cl, size_t cr) {
		if(cl == cr) {
			return;
		}
		size_t mid = (cl+cr)/2;
		Node& p1 = nodes[cur.lchild = new_node()];
		Node& p2 = nodes[cur.rchild = new_node()];
		build(p1, cl, mid, v);
		build(p2, mid+1, cr, v);
		cur.data = p1.data + p2.data;
	}
	int64_t query(size_t l, size_t r, Node& cur, size_t cl, size_t cr) {
		if(r < cl || cr < l) {
			return 0;
		}
		if(l <= cl && cr <= r) {
			return cur.data;
		}
		size_t mid = (cl+cr)/2;
		Node& p1 = nodes[cur.lchild];
		Node& p2 = nodes[cur.rchild];
		auto ret1 = query(l,r,p1,cl,mid);
		auto ret2 = query(l,r,p2,mid+1,cr);
		return ret1+ret2;
	}
	void update(size_t pos, int64_t val, Node& cur, Node& prev, size_t cl, size_t cr) {
		if(pos < cl || cr < pos) {
			return;
		}
		if(cl == cr) {
			cur.data = prev.data + val;
			return;
		}
		size_t mid = (cl+cr)/2;
		if(pos <= mid) {
			cur.lchild = new_node();
			cur.rchild = prev.rchild;
		} else {
			cur.lchild = prev.lchild;
			cur.rchild = new_node();
		}
		Node& p1 = nodes[cur.lchild];
		Node& prev1 = nodes[prev.lchild];
		Node& p2 = nodes[cur.rchild];
		Node& prev2 = nodes[prev.rchild];
		update(pos, val, p1, prev1, cl, mid);
		update(pos, val, p2, prev2, mid+1, cr);
		cur.data = p1.data + p2.data;
	}
	int64_t query(size_t l, size_t r, size_t time) {
		Node& cur = nodes[roots[time]];
		return query(l,r,cur,0,size-1);
	}
	void update(size_t pos, int64_t val) {
		Node& prev = nodes[roots.back()];
		roots.push_back(new_node());
		Node& cur = nodes[roots.back()];
		update(pos,val,cur,prev,0,size-1);
	}
};
