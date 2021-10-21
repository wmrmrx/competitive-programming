struct PersistentSeg {
	struct Node {
		Node *lchild, *rchild;
		int data;
		Node() {
			lchild = rchild = NULL;
			data = 0;
		}
	};
	int max_range;
	vector<Node*> root;
	PersistentSeg(int _max_range, int v[]) {
		max_range = _max_range;
		root.push_back(new Node);	
		build(root[0],1,max_range,v);
	}
	void update_node_data(Node* cur) {
		cur->data = cur->lchild->data + cur->rchild->data;
	}
	void build(Node* cur, int nl, int nr, int v[]) {
		if(nl == nr) {
			cur->data = v[nl];
			return;
		}
		int mid = (nl+nr)/2;
		cur->lchild = new Node;
		cur->rchild = new Node;
		build(cur->lchild,nl,mid,v); 
		build(cur->rchild,mid+1,nr,v);
		update_node_data(cur);
	}
	void upd(Node* cur, Node* prev, int nl, int nr, int pos, int val) {
		if(nl == nr) {
			cur->data = val;
			return;
		}
		int mid = (nl+nr)/2;
		if(pos <= mid) {
			cur->lchild = new Node;
			cur->rchild = prev->rchild;
			upd(cur->lchild,prev->lchild,nl,mid,pos,val);
		} else {
			cur->rchild = new Node;
			cur->lchild = prev->lchild;
			upd(cur->rchild,prev->rchild,mid+1,nr,pos,val);
		}
		update_node_data(cur);
	}
	void update(int pos, int val) {
		Node* prev = root.back();	
		root.push_back(new Node);
		upd(root.back(),prev,1,max_range,pos,val);
	}
	int qry(Node* cur, int nl, int nr, int ql, int qr) {
		if(nr < ql || qr < nl) {
			return 0;
		}
		if(ql <= nl && nr <= qr) {
			return cur->data;
		}
		int mid = (nl+nr)/2;
		return qry(cur->lchild,nl,mid,ql,qr) + qry(cur->rchild,mid+1,nr,ql,qr);
	}
	int query(int l, int r, int time) {
		return qry(root[time],1,max_range,l,r);
	}
};
