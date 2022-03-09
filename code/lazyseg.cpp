struct LazySeg {
	struct Data {
		int64_t x;
		// assert( data1.merge(Data()) = data1 )
		Data(): x(0) {}
		Data(int64_t x): x(x) {}
		Data merge(const Data& rhs) const { 
			return Data(x+rhs.x);
		}
	};
	struct LazyData {
		int64_t x;
		// assert( LazyData().needs_propagation() == false )
		LazyData() : x(0) {}
		bool needs_propagation() const {
			return x != 0;
		}
		void propagate(LazyData& child) const {
			child.x += x;
		}
		void refresh(Data& data, size_t cl, size_t cr) {
			data.x += (cr-cl+1)*x;
			x = 0;
		}
		void update(const Data data) {
			x += data.x;
		}
	};
	struct Node {
		size_t lchild, rchild;
		Data data;
		LazyData pool;
		Node(): lchild(0), rchild(0), data(), pool() {}
	};
	const size_t size;
	vector<Node> nodes;
	LazySeg(size_t size): size(size) {
		nodes.reserve(2*size-1);
		new_node();
		build(nodes[0],0,size-1);
	}
	size_t new_node() {
		nodes.push_back(Node());
		return nodes.size()-1;
	}
	void refresh(Node& cur, size_t cl, size_t cr) {
		if(cur.pool.needs_propagation()) {
			if(cl < cr) {
				cur.pool.propagate(nodes[cur.lchild].pool);
				cur.pool.propagate(nodes[cur.rchild].pool);
			}
			cur.pool.refresh(cur.data, cl, cr);
		}
	}
	void build(Node& cur, size_t cl, size_t cr) {
		if(cl == cr) { 
			cur.data = Data();
			return; 
		}
		size_t mid = (cl+cr)/2;
		Node& p1 = nodes[cur.lchild = new_node()];
		Node& p2 = nodes[cur.rchild = new_node()];
		build(p1, cl, mid);
		build(p2, mid+1, cr);
		cur.data = p1.data.merge(p2.data);
	}
	Data query(const size_t l, const size_t r, Node& cur, size_t cl, size_t cr) {
		refresh(cur, cl, cr);
		if(r < cl || cr < l) {
			return Data();
		}
		if(l <= cl && cr <= r) return cur.data;
		size_t mid = (cl+cr)/2;
		Data ret1 = query(l,r,nodes[cur.lchild],cl,mid);
		Data ret2 = query(l,r,nodes[cur.rchild],mid+1,cr);
		return ret1.merge(ret2);
	}
	void update(const size_t l, const size_t r, const Data data, Node& cur, size_t cl, size_t cr) {
		if(l <= cl && cr <= r) {
			cur.pool.update(data);
			refresh(cur, cl, cr);
			return;
		}
		refresh(cur, cl, cr);
		if(r < cl || cr < l) return;
		size_t mid = (cl+cr)/2;
		Node& p1 = nodes[cur.lchild];
		Node& p2 = nodes[cur.rchild];
		update(l, r, data, p1, cl, mid);
		update(l, r, data, p2, mid+1, cr);
		cur.data = p1.data.merge(p2.data);
	}
	Data query(size_t l, size_t r) {
		Node& cur = nodes[0];
		return query(l,r,cur,0,size-1);
	}
	void update(size_t l, size_t r, const Data data) {
		Node& cur = nodes[0];
		update(l,r,data,cur,0,size-1);
	}
};
