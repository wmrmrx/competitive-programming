struct Seg {
	struct Node {
		Node *lchild, *rchild;
		int data;
		Node() {
			lchild = rchild = NULL;
			data = INF;
		}
	};
	int size;
	vector<Node> nodes;
	Seg(int _size, int v[]) {
		size = _size;
		nodes.reserve(2*size-1);
		nodes.push_back(Node());
		build(&nodes.back(),1,size,v);
	}
	void build(Node* cur, int nl, int nr, int v[]) {
		if(nl == nr) {
			cur->data = v[nl];
			return;
		}
		int mid = (nl+nr)/2;
		nodes.push_back(Node());
		cur->lchild = &nodes.back();
		build(cur->lchild,nl,mid,v);
		nodes.push_back(Node());
		cur->rchild = &nodes.back();
		build(cur->rchild,mid+1,nr,v);
		cur->data = min(cur->lchild->data,cur->rchild->data);
	}
	void upd(Node* cur, int nl, int nr, int pos, int val) {
		if(nl == nr) {
			cur->data = val;
			return;
		}
		int mid = (nl+nr)/2;
		if(pos <= mid) {
			upd(cur->lchild,nl,mid,pos,val);
		} else {
			upd(cur->rchild,mid+1,nr,pos,val);
		}
		cur->data = min(cur->lchild->data,cur->rchild->data);
	}
	void update(int pos, int val) {
		upd(&nodes[0],1,size,pos,val);
	}
	int qry(Node* cur, int nl, int nr, int ql, int qr) {
		if(nr < ql || qr < nl) {
			return INF;
		}
		if(ql <= nl && nr <= qr) {
			return cur->data;
		}
		int mid = (nl+nr)/2;
		return min(qry(cur->lchild,nl,mid,ql,qr), qry(cur->rchild,mid+1,nr,ql,qr));
	}
	int query(int l, int r) {
		return qry(&nodes[0], 1, size, l, r);
	}
};
