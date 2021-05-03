//链式前向星存图
struct edge {
	int v, to;
} e[N];
int h[N], cnt, n;
void add(int u, int v) {
	e[cnt] = {v, h[u] };
	h[u] = cnt++;
}

void ini() {
	memset(h, -1, sizeof h);
}

//线段树部分
struct Sgt
{
	const static int N = 1e6;
	struct node
	{
		int l, r, sum, lazy;
	}t[N << 1];
	int a[N];

	void pushdown(int p) {
		t[p].sum += (t[p].r - t[p].l + 1) * t[p].lazy;
		t[p << 1].lazy += t[p].lazy; t[p << 1 | 1].lazy += t[p].lazy;
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
			t[p].sum = a[l];
			return;
		}
		int mid = l + r >> 1;
		build(l, mid, p << 1);
		build(mid + 1, r, p << 1 | 1);
		pushup(p);
	}

	void add(int l, int r, int k, int p) {
		int L = t[p].l, R = t[p].r;
		pushdown(p);
		if (l <= L && r >= R) {
			t[p].lazy += k;
			return;
		}
		int mid = L + R >> 1;
		if (l <= mid) add(l, r, k, p << 1);
		if (r > mid) add(l, r, k, p << 1 | 1);
		pushup(p);
	}

	int query(int l, int r, int p) {
		int L = t[p].l, R = t[p].r;
		pushdown(p);
		if (l <= L && r >= R) return t[p].sum;
		int mid = L + R >> 1;
		int sum = 0;
		if (l <= mid) sum += query(l, r, p << 1);
		if (r > mid) sum += query(l, r, p << 1 | 1);
		pushup(p);
		return sum;
	}
};
//树剖部分
struct sp
{
	const static int N = 1e6 + 100;
	//树剖数组
	Sgt sgt;
	int f[N]; //f[i]: i的父节点
	int son[N]; //son[i]: 每个点的重儿子	
	int dep[N]; //dep[i]: i的深度
	int size[N]; //size[i]: 以i为根的子树的大小
	int top[N]; //top[i]： i所在链的顶点
	int map[N]; //map[i]: i对应的dfs序编号
	int val[N]; //val[i]: i的结点权值,
	int rmap[N]; //rmap[map[i]] = i, dfs编号对应的原结点
	int cnt;//dfs序编号
	//求每个点的深度, 父节点, 子树大小
	void dfs1(int u, int fa) {
		dep[u] = dep[fa] + 1; //u结点深度为父节点深度+1
		size[u] = 1;
		f[u] = fa;
		for (int i = h[u], v = e[i].v; ~i; i = e[i].to, v = e[i].v) {
			if (v != fa) {
				dfs1(v, u);
				size[u] += size[v]; //u子树加上所有子树大小
				if (!son[u] || size[v] > size[son[u]]) son[u] = v; //若没有重儿子或当期儿子更重更新
			}
		}
	}
	//topf: u所在链的最顶端结点
	void dfs2(int u, int topf) {
		map[u] = ++cnt;
		rmap[cnt] = u;
		top[u] = topf;
		//若有重儿子优先搜索重儿子, 这样所有链上的节点编号就是连续的
		if (son[u]) dfs2(son[u], topf);
		for (int i = h[u], v = e[i].v; ~i; i = e[i].to, v = e[i].v) {
			if (v != f[u] && v != son[u]) {
				dfs2(v, v);
			}
		}
	}
	void ini(int rt) {
		dfs1(rt, 0);
		dfs2(rt, rt);
	}

	int lca(int u, int v) {
		while (top[u] != top[v]) {
			if (dep[top[u]] < dep[top[v]]) swap(u, v);
			u = f[top[u]];
		}
		return dep[u] < dep[v] ? u : v;
	}
	int querySum(int u, int v) {
		int ans = 0;
		while (top[u] != top[v]) {
			if (dep[top[u]] < dep[top[v]]) swap(u, v);
			ans = (ans + sgt.query(map[top[u]], map[u], 1));
			u = f[top[u]];

		}
		u = map[u], v = map[v];
		ans = (ans + sgt.query(min(u, v), max(u, v), 1));
		return ans;
	}
	void add(int u, int v, int k) {

		while (top[u] != top[v]) {
			if (dep[top[u]] < dep[top[v]]) swap(u, v);
			sgt.add(map[top[u]], map[u], k, 1);
			u = f[top[u]];
		}
		u = map[u], v = map[v];
		sgt.add(min(u, v), max(u, v), k, 1);
	}
	int querySum(int u) {
		return sgt.query(map[u], map[u] + size[u] - 1, 1);
	}

	void add(int u, int k) {
		sgt.add(map[u], map[u] + size[u] - 1, k, 1);
	}

}sp;

