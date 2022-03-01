struct LazySeg {
	struct Node {
		Node *lchild, *rchild;
		int data;
		int pooled_data;
		Node() {
			lchild = rchild = NULL;
			data = 0;
			pooled_data = 0;
		}
	};
	int size;
	vector<Node> nodes;
	LazySeg(int _size, int v[]) {
		size = _size;
		nodes.reserve(2*size-1);
		nodes.push_back(Node());
		build(&nodes[0],1,size,v);
	}
	void build(Node* cur, int nl, int nr, int v[]) {
		if(nl == nr) {
			cur->data = v[nl];
			return;
		}
		int mid = (nl+nr)/2;
		nodes.push_back(Node());
		cur->lchild = &nodes.back();
		nodes.push_back(Node());
		cur->rchild = &nodes.back();
		build(cur->lchild,nl,mid,v); 
		build(cur->rchild,mid+1,nr,v);
		cur->data = cur->lchild->data + cur->rchild->data;
	}
	void refresh(Node* cur, int nl, int nr) {
		if(cur->pooled_data != 0) {
			cur->data += cur->pooled_data * (nr - nl + 1);
			if(nl != nr) {
				cur->lchild->pooled_data += cur->pooled_data;
				cur->rchild->pooled_data += cur->pooled_data;
			}
			cur->pooled_data = 0;
		}
	}
	void upd(Node* cur, int nl, int nr, int ql, int qr, int val) {
		refresh(cur,nl,nr);
		if(nr < ql || qr < nl) {
			return;
		}
		if(ql <= nl && nr <= qr) {
			cur->pooled_data += val;
			return;
		}
		int mid = (nl+nr)/2;
		upd(cur->lchild, nl, mid, ql, qr, val);
		upd(cur->rchild, mid+1, nr, ql, qr, val);
		refresh(cur->lchild,nl,mid); 
		refresh(cur->rchild,mid+1,nr);
		cur->data = cur->lchild->data + cur->rchild->data;
	}
	void update(int l, int r, int val) {
		upd(&nodes[0],1,size,l,r,val);
	}
	int qry(Node* cur, int nl, int nr, int ql, int qr) {
		refresh(cur,nl,nr);
		if(nr < ql || qr < nl) {
			return 0;
		}
		if(ql <= nl && nr <= qr) {
			return cur->data;
		}
		int mid = (nl+nr)/2;
		return qry(cur->lchild,nl,mid,ql,qr) + qry(cur->rchild,mid+1,nr,ql,qr);
	}
	int query(int l, int r) {
		return qry(&nodes[0],1,size,l,r);
	}
};
