struct Seg {
	constexpr size_t OOB=1<<31;
	struct Data {
		int64_t x;
		Data(const int64_t x=0): x(x) {}
		Data merge(const Data& rhs) const { 
			return Data(x+rhs.x);
		}
	};
	struct Node {
		size_t lchild, rchild;
		Data data;
		Node(): lchild(OOB), rchild(OOB), data() {}
	};
	const size_t size;
	vector<Node> nodes;
	Seg(size_t size): size(size) {
		nodes.reserve(2*size-1);
		new_node();
		build(nodes[0],0,size-1);
	}
	size_t new_node() {
		nodes.push_back(Node());
		return nodes.size()-1;
	}
	void build(Node& cur, size_t cl, size_t cr) {
		if(cl == cr) { 
			return Data(); 
		}
		size_t mid = (cl+cr)/2;
		Node& p1 = nodes[cur.lchild = new_node()];
		Node& p2 = nodes[cur.rchild = new_node()];
		build(p1, cl, mid, v);
		build(p2, mid+1, cr, v);
		cur.data = p1.data.merge(p2.data);
	}
	Data query(const size_t l, const size_t r, Node& cur, size_t cl, size_t cr) {
		if(r < cl || cr < l) {
			Data empty();
			return empty;
		}
		if(l <= cl && cr <= r) return cur.data;
		size_t mid = (cl+cr)/2;
		Data ret1 = query(l,r,nodes[cur.lchild],cl,mid);
		Data ret2 = query(l,r,nodes[cur.rchild],mid+1,cr);
		return ret1.merge(ret2);
	}
	int64_t lower_bound(int64_t val, Node& cur, size_t cl, size_t cr) {
		if(cl == cr) return cl;
		size_t mid = (cl+cr)/2;
		Node& p1 = nodes[cur.lchild];
		Node& p2 = nodes[cur.rchild];
		if(p1.data.x < val) return lower_bound(val-p1.data.x,p2,mid+1,cr);
		else return lower_bound(val,p1,cl,mid);
	}
	void update(const size_t pos, const int64_t val, Node& cur, size_t cl, size_t cr) {
		if(pos < cl || cr < pos) return;
		if(cl == cr) { 
			cur.data.x += val; 
			return; 
		}
		size_t mid = (cl+cr)/2;
		update(pos, val, nodes[cur.lchild], cl, mid);
		update(pos, val, nodes[cur.rchild], mid+1, cr);
		cur.data = p1.data.merge(p2.data);
	}
	int64_t query(size_t l, size_t r) {
		Node& cur = nodes[0];
		return query(l,r,cur,0,size-1).x;
	}
	size_t lower_bound(size_t l, size_t r, int64_t val) {
		Node& cur = nodes[0];
		int64_t q = query(l,r);
		if(q < val) return -1;
		val += query(0, r) - q;
		return lower_bound(val,cur,0,size-1);
	}
	void update(size_t pos, int64_t val) {
		Node& cur = nodes[0];
		update(pos,val,cur,0,size-1);
	}
};
