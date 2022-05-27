mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
template <typename T>
struct Treap {
	struct node {
		int cnt, h;
		T data;
		array<node*,2> ch;

		node(T data=0): cnt(1), h(rng()), data(data), ch({0, 0}) {}

		node* refresh() {
			cnt = 1;
			for(int side: {0, 1}) 
				cnt += ch[side] ? ch[side]->cnt : 0;
			return this;
		}
	};

	int sz;
	node *root;
	unique_ptr<node[]> arena;

	Treap(int prealloc): sz(0), root(0), arena(new node[prealloc]) {}

	node* new_node(T data) {
		arena[sz] = node(data);
		return &arena[sz++];
	}

	node* merge(node *l, node *r) {
		if(!l || !r) return l ? l : r;
		if(l->h < r->h) {
			r->ch[0] = merge(l, r->ch[0]);
			return r->refresh();
		}
		else {
			l->ch[1] = merge(l->ch[1], r);
			return l->refresh();
		}
	}

	array<node*, 2> split(node* a, int pos, int rank = 0) {
		if(!a) return {0, 0};
		int cur_rank = rank + (a->ch[0] ? a->ch[0]->cnt : 0);
		if(pos <= cur_rank) {
			auto res = split(a->ch[0], pos, rank);
			a->ch[0] = res[1];
			return { res[0], a->refresh() };
		} else {
			auto res = split(a->ch[1], pos, cur_rank+1);
			a->ch[1] = res[0];
			return { a->refresh(), res[1] };
		}
	}

	void insert(T data, int idx) {
		if(!root) root = new_node(data);
		else {
			node* n = new_node(data);
			auto s = split(root, idx);
			s[0] = merge(s[0], n);
			root = merge(s[0], s[1]);
		}
	}

	void erase(int idx) {
		auto s1 = split(root, idx);
		auto s2 = split(s1[1], 1);
		root = merge(s1[0], s2[1]);
	}

	T& get(int idx) {
		auto* cur = root;
		int rank = 0;
		int cur_rank = rank + (cur->ch[0] ? cur->ch[0]->cnt : 0);
		while(cur_rank != idx) {
			if(idx < cur_rank) cur = cur->ch[0];
			else cur = cur->ch[1], rank = cur_rank+1;
			cur_rank = rank + (cur->ch[0] ? cur->ch[0]->cnt : 0);
		}
		return cur->data;
	}
};
