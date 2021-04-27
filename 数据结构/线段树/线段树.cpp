namespace sgt {
	const int N = 1e6 + 100;
	struct node
	{
		int l, r;
		int lazy;
		int sum;
	}t[N];
	int val[N];
	void pushdown(int p) {
		t[p].sum += t[p].lazy * (t[p].r - t[p].l + 1);
		t[p << 1].lazy += t[p].lazy;
		t[p << 1 | 1].lazy += t[p].lazy;
		t[p].lazy = 0;
	}

	void pushup(int p) {
		pushdown(p << 1);
		pushdown(p << 1 | 1);
		t[p].sum = t[p << 1].sum + t[p << 1 | 1].sum;
	}

	void build(int l, int r, int p) {
		t[p].l = l; t[p].r = r;
		if (l >= r) {
			t[p].sum = val[l];
			t[p].lazy = 0;
			return;
		}
		int mid = l + r >> 1;
		build(l, mid, p << 1);
		build(mid + 1, r, p << 1 | 1);
		pushup(p);

	}
	void modify(int l, int r, int k, int p) {
		int ll = t[p].l;
		int rr = t[p].r;
		if (l <= ll && r >= rr) {
			t[p].lazy += k;
			pushdown(p);
			return;
		}
		pushdown(p);
		int mid = ll + rr >> 1;
		if (l <= mid) modify(l, r, k, p << 1);
		if (r > mid) modify(l, r, k, p << 1 | 1);
		pushup(p);
	}
	int query(int l, int r, int p) {
		int ll = t[p].l;
		int rr = t[p].r;
		pushdown(p);
		if (l <= ll && r >= rr) {
			return t[p].sum;
		}
		int mid = ll + rr >> 1;
		int ans = 0;
		if (l <= mid) ans += query(l, r, p << 1);
		if (r > mid) ans += query(l, r, p << 1 | 1);
		return ans;
	}
}