struct PersistentSeg {
	struct Node {
		int l, r;
		Node *lchild, *rchild;
		int data;
		Node(int _l, int _r) {
			l = _l; r = _r;
			lchild = rchild = NULL;
			data = 0;
		}
	};
	int max_range;
	vector<Node*> root;
	PersistentSeg(int _max_range, int v[]) {
		max_range = _max_range;
		root.push_back(new Node(1,max_range));	
		build(root[0],v);
	}
	void build(Node* cur, int v[]) {
		if(cur->l == cur->r) {
			cur->data = v[cur->l];
			return;
		}
		int mid = (cur->l+cur->r)/2;
		cur->lchild = new Node(cur->l,mid);
		cur->rchild = new Node(mid+1,cur->r);
		build(cur->lchild,v); 
		build(cur->rchild,v);
		cur->data = cur->lchild->data + cur->rchild->data;
	}
	void upd(Node* cur, Node* prev, int pos, int val) {
		if(cur->l == cur->r) {
			cur->data = val;
			return;
		}
		int mid = (cur->l+cur->r)/2;
		if(pos <= mid) {
			cur->lchild = new Node(cur->l,mid);
			cur->rchild = prev->rchild;
			upd(cur->lchild,prev->lchild,pos,val);
		} else {
			cur->rchild = new Node(mid+1,cur->r);
			cur->lchild = prev->lchild;
			upd(cur->rchild,prev->rchild,pos,val);
		}
		cur->data = cur->lchild->data + cur->rchild->data;
	}
	void update(int pos, int val) {
		Node* prev = root.back();	
		root.push_back(new Node(1,max_range));
		upd(root.back(),prev,pos,val);
	}
	int qry(Node* cur, int l, int r) {
		if(cur->r < l || r < cur->l) {
			return 0;
		}
		if(l <= cur->l && cur->r <= r) {
			return cur->data;
		}
		return qry(cur->lchild,l,r) + qry(cur->rchild,l,r);
	}
	int query(int l, int r, int time) {
		return qry(root[time],l,r);
	}
};
