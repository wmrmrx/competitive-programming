struct Seg {
	struct Data {
		int64_t x;
		// assert( data1.merge(Data()) = data1 )
		Data(): x(0) {}
		Data(int64_t x): x(x) {}
		Data merge(const Data& rhs) const { 
			return Data(x+rhs.x);
		}
		void update(const Data rhs) {
			x += rhs.x;
		}
	};
	struct Node {
		size_t lchild, rchild;
		Data data;
		Node(): lchild(0), rchild(0), data() {}
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
		if(r < cl || cr < l) {
			return Data();
		}
		if(l <= cl && cr <= r) return cur.data;
		size_t mid = (cl+cr)/2;
		Data ret1 = query(l,r,nodes[cur.lchild],cl,mid);
		Data ret2 = query(l,r,nodes[cur.rchild],mid+1,cr);
		return ret1.merge(ret2);
	}
	void update(const size_t pos, const Data data, Node& cur, size_t cl, size_t cr) {
		if(pos < cl || cr < pos) return;
		if(cl == cr) { 
			cur.data.update(data);
			return; 
		}
		size_t mid = (cl+cr)/2;
		Node& p1 = nodes[cur.lchild];
		Node& p2 = nodes[cur.rchild];
		update(pos, data, p1, cl, mid);
		update(pos, data, p2, mid+1, cr);
		cur.data = p1.data.merge(p2.data);
	}
	Data query(size_t l, size_t r) {
		Node& cur = nodes[0];
		return query(l,r,cur,0,size-1);
	}
	void update(size_t pos, Data data) {
		Node& cur = nodes[0];
		update(pos,data,cur,0,size-1);
	}
};
