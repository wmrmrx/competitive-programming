mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
template <typename DATA>
struct Treap {
	struct node {
		int cnt, h;
		DATA data;
		node* dad;
		array<node*,2> ch;

		node() {}
		node(DATA data): cnt(1), h(rng()), data(data), dad(0), ch({0, 0}) {}

		node* refresh() {
			cnt = 1;
			for(node* x: ch) if(x) {
				x->dad = this;
				cnt += x->cnt;
			}
			return this;
		}
	};

	int sz;
	node *root;
	unique_ptr<node[]> arena;

	Treap(int prealloc): sz(0), root(0), arena(new node[prealloc]) {}

	node* new_node(DATA data) {
		arena[sz] = node(data);
		return &arena[sz++];
	}

	int cnt(node* x) { return x ? x->cnt : 0; }

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

	array<node*, 2> split(node* x, int pos, int rank = 0) {
		if(!x) return {0, 0};
		rank += cnt(x->ch[0]);
		if(pos <= rank) {
			auto res = split(x->ch[0], pos, rank-cnt(x->ch[0]));
			x->ch[0] = res[1];
			return { res[0], x->refresh() };
		} else {
			auto res = split(x->ch[1], pos, rank+1);
			x->ch[1] = res[0];
			return { x->refresh(), res[1] };
		}
	}

	void insert(DATA data, int idx) {
		auto s = split(root, idx);
		s[0] = merge(s[0], new_node(data));
		root = merge(s[0], s[1]);
	}

	void erase(int idx) {
		auto s1 = split(root, idx);
		auto s2 = split(s1[1], 1);
		root = merge(s1[0], s2[1]);
	}

	int rank(node* x) {
		int res;
		for(res = cnt(x->ch[0]); x != root; x=x->dad) {
			node* l = x->dad->ch[0];
			if(l != x) res += 1 + cnt(l);
		}
		return res;
	}

	node* get(int idx) {
		node* x = root;
		for(int rank = cnt(x->ch[0]); rank != idx; rank += cnt(x->ch[0])) {
			if(rank < idx) rank++, x = x->ch[1];
			else rank -= cnt(x->ch[0]), x = x->ch[0];
		}
		return x;
	}
};
