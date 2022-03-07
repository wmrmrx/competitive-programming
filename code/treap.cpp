constexpr size_t OOB=1<<31;
struct Treap {
	struct Data {
		int64_t x;
		Data(const int64_t x=0): x(x) {}
		Data merge(const Data& rhs) const { 
			return Data(x+rhs.x);
		}
	};
	struct Node {
		size_t lchild, rchild;
		uint32_t sub;
		const uint32_t h;
		Data data;
		Node(uint32_t h): lchild(OOB), rchild(OOB), sub(1), h(h), data() {}
	};
	size_t root;
	vector<uint32_t> h;
	vector<Node> nodes;
	size_t new_node() {
		nodes.push_back(Node(h[nodes.size()]));
		return nodes.size()-1;
	}
	vector<uint32_t> random_permutation(const size_t size) const {
		vector<uint32_t> ret(size);
		iota(ret.begin(),ret.end(),0);
		mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
		shuffle(ret.begin(), ret.end(), rng);
		return ret;
	}
	Treap(const size_t size=0): root(OOB), h(random_permutation(size)) {
		nodes.reserve(size);
	}
	size_t cnt_left(const Node& t) const { return t.lchild==OOB?0:(size_t)nodes[t.lchild].sub; }
	size_t cnt_right(const Node& t) const { return t.rchild==OOB?0:(size_t)nodes[t.rchild].sub; }
	void refresh(const Node& t) { t.sub=1+cnt_left(t)+cnt_right(t); }
	void split(const size_t pos, size_t idx, size_t cur, size_t& tl, size_t& tr) {
		if(cur == OOB) { tl = tr = OOB; return; }
		size_t cur_idx = idx + cnt_left(nodes[cur]);
		if(pos < cur_idx) tr=cur, split(pos,idx,nodes[cur].lchild,tl,nodes[cur].lchild);
		else tl=cur, split(pos,cur_idx+1,nodes[cur].rchild,nodes[cur].rchild,tr);
		refresh(cur);
	}
	void merge(size_t tl, size_t tr, size_t& dest) {
		if(tl==OOB||tr==OOB) { dest = tl!=OOB?tl:tr; return; }
		if(nodes[tl].h < nodes[tr].h) dest=tr, merge(tl,nodes[tr].lchild,nodes[tr].lchild);
		else dest=tl, merge(nodes[tl].rchild,tr,nodes[tl].rchild);
		refresh(dest);
	}
	int64_t& find(size_t index) {
		if(root == OOB || nodes[root].sub >= index) return nullptr;
		size_t cur_idx = cnt_left(nodes[cur]);
		size_t cur = root;
		while(cur_index != index) {
			if(index < cur_index) {
				cur_idx-=cnt_left(nodes[cur]);
				cur=nodes[cur].lchild;
				cur_idx+=cnt_left(nodes[cur]);
			} else {
				cur_idx++;
				cur=nodes[cur].rchild;
			}
		}
		return nodes[cur].data.x;
	}
	// TODO
	void insert(size_t index) {

	}
	void erase(size_t index) {

	}
};




