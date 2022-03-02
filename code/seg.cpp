struct Seg {
	struct Node {
		size_t lchild, rchild;
		int64_t data;
		Node(): lchild(0), rchild(0), data(0) {}
	};
	const size_t size;
	vector<Node> nodes;
	size_t new_node() {
		nodes.push_back(Node());
		return nodes.size()-1;
	}
	template <typename T> Seg(size_t size, const T v[]): size(size) {
		nodes.reserve(2*size-1);
		new_node();
		build(nodes[0],0,size-1,v);
	}
	template <typename T> void build(Node& cur, size_t cl, size_t cr, const T v[]) {
		if(cl == cr) {
			cur.data = v[cl];
			return;
		}
		size_t mid = (cl+cr)/2;
		cur.lchild = new_node();
		Node& p1 = nodes[cur.lchild];
		cur.rchild = new_node();
		Node& p2 = nodes[cur.rchild];
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
		return query(l,r,p1,cl,mid) + query(l,r,p2,mid+1,cr);
	}
	size_t lower_bound(int64_t val, Node& cur, size_t cl, size_t cr) {
		if(cl == cr) {
			return cl;
		}
		size_t mid = (cl+cr)/2;
		Node& p1 = nodes[cur.lchild];
		Node& p2 = nodes[cur.rchild];
		if(p1.data < val) {
			return lower_bound(val - p1.data, p2, mid+1, cr);
		} else {
			return lower_bound(val, p1, cl, mid);
		}
	}
	void update(size_t pos, int64_t val, Node& cur, size_t cl, size_t cr) {
		if(pos < cl || cr < pos) {
			return;
		}
		if(cl == cr) {
			cur.data += val;
			return;
		}
		size_t mid = (cl+cr)/2;
		Node& p1 = nodes[cur.lchild];
		Node& p2 = nodes[cur.rchild];
		update(pos, val, p1, cl, mid);
		update(pos, val, p2, mid+1, cr);
		cur.data = p1.data + p2.data;
	}
	int64_t query(size_t l, size_t r) {
		Node& cur = nodes[0];
		return query(l,r,cur,0,size-1);
	}
	size_t lower_bound(int64_t val) {
		Node& cur = nodes[0];
		return lower_bound(val,cur,0,size-1);
	}
	void update(size_t pos, int64_t val) {
		Node& cur = nodes[0];
		update(pos,val,cur,0,size-1);
	}
};
