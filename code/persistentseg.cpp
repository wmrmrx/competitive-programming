struct PersistentSeg {
	struct Node {
		int lrange, rrange;
		Node *lchild, *rchild;
		int data;
		Node(int _lrange, int _rrange) {
			lrange = _lrange; rrange = _rrange;
			lchild = rchild = NULL;
			data = 0;
		}
	};
	void update_node_data(Node* cur) {
		cur->data = cur->lchild->data + cur->rchild->data;
	}
	int max_range;
	vector<Node*> root;
	PersistentSeg(int _max_range, int v[]) {
		max_range = _max_range;
		root.push_back(new Node(1,max_range));	
		build(root[0],v);
	}
	void build(Node* cur, int v[]) {
		if(cur->lrange == cur->rrange) {
			cur->data = v[cur->lrange];
			return;
		}
		int mid = (cur->lrange+cur->rrange)/2;
		cur->lchild = new Node(cur->lrange,mid);
		cur->rchild = new Node(mid+1,cur->rrange);
		build(cur->lchild,v); 
		build(cur->rchild,v);
		update_node_data(cur);
	}
	void upd(Node* cur, Node* prev, int pos, int val) {
		if(cur->lrange == cur->rrange) {
			cur->data = val;
			return;
		}
		int mid = (cur->lrange+cur->rrange)/2;
		if(pos <= mid) {
			cur->lchild = new Node(cur->lrange,mid);
			cur->rchild = prev->rchild;
			upd(cur->lchild,prev->lchild,pos,val);
		} else {
			cur->rchild = new Node(mid+1,cur->rrange);
			cur->lchild = prev->lchild;
			upd(cur->rchild,prev->rchild,pos,val);
		}
		update_node_data(cur);
	}
	void update(int pos, int val) {
		Node* prev = root.back();	
		root.push_back(new Node(1,max_range));
		upd(root.back(),prev,pos,val);
	}
	int qry(Node* cur, int l, int r) {
		if(cur->rrange < l || r < cur->lrange) {
			return 0;
		}
		if(l <= cur->lrange && cur->rrange <= r) {
			return cur->data;
		}
		return qry(cur->lchild,l,r) + qry(cur->rchild,l,r);
	}
	int query(int l, int r, int time) {
		return qry(root[time],l,r);
	}
};
