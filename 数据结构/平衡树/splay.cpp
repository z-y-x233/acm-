template<typename T> 
class Splay {
public:
	//返回最大的小于x的元素
	T upper(T x) {
		find(x);
		if (tree[rt] >= x) {
			int p = pre(rt);
			if (p)
				return tree[p];
			else
				return x;
		}
		return tree[rt];
	}
	//返回最小的大于x的元素
	T lower(T x) {
		find(x);
		if (tree[rt] <= x) {
			int p = succ(rt);
			if (p)
				return tree[p];
			else
				return x;
		}
		return tree[rt];
	}
	


	//将x的前驱或者后继旋转到根
	void find(T x) {
		int cur = rt;
		while (tree[cur] != x && son[cur][x > tree[cur]]) {
			cur = son[cur][x > tree[cur]];
		}
		splay(cur);
	}
	//返回x的前驱节点
	int pre(int x) {
		splay(x);
		int cur = son[x][0];
		while (cur&&son[cur][1])
			cur = son[cur][1];
		return cur;
	}
	//返回x的后继节点
	int succ(int x) {
		splay(x);
		int cur = son[x][1];
		while (cur&&son[cur][0])
			cur = son[cur][0];
		return cur;
	}
	//插入一个元素x
	void insert(T x) {
		if (!sz) {
			int cur = ++sz;
			tree[cur] = x;
			re[cur] = size[cur] = 1;
			f[cur] = son[cur][0] = son[cur][1] = 0;
			rt = cur;
		}
		else {
			int cur = rt;
			while (tree[cur] != x && son[cur][x > tree[cur]]) {
				cur = son[cur][x > tree[cur]];
			}
			if (tree[cur] == x) {
				re[cur]++;
			}
			else {
				int newnode;
				if (rec[0])
					newnode = rec[rec[0]--];
				else
					newnode = ++sz;
				tree[newnode] = x;
				son[newnode][0] = son[newnode][1] = 0;
				re[newnode] = size[newnode] = 1;
				f[newnode] = cur;
				son[cur][x > tree[cur]] = newnode;
			}
			splay(cur);
		}
	}
	//删除一个元素x
	int del(T x) {
		find(x);
		int cur = rt;
		if (tree[cur] == x) {
			if (re[cur] > 1) {
				re[cur]--, size[cur]--;
			}
			else {
				int p = pre(cur);
				int s = succ(cur);
				if (!p && !s) {
					clear(cur);
				}
				else if (!p&&s) {
					rt = son[cur][1];
					f[rt] = 0;
					clear(cur);
				}
				else if (p && !s) {
					rt = son[cur][0];
					f[rt] = 0;
					clear(cur);
				}
				else {
					splay(p);
					splay(s, p);
					son[s][0] = 0;
					clear(cur);
					update(s);
					update(p);
				}
			}
			return 1;
		}
		else
			return 0;
	}
	//查询x的排名
	int rank(T x) {
		find(x);
		int cur = rt;
		if (tree[cur] == x) {
			return size[son[cur][0]] + 1;
		}
		else {
			if (tree[cur] > x)
				return size[son[cur][0]] + 1;
			else {
				int s = succ(cur);
				splay(s);
				return size[son[cur][0]] + 1;
			}
		}
	}
	//查询排名为k的元素
	int kth(int k) {
		int cur = rt;
		while (1) {
			if (k <= size[son[cur][0]]) {
				cur = son[cur][0];
			}
			else if (k <= size[son[cur][0]] + re[cur]) {
				return cur;
			}
			else {
				k -= size[son[cur][0]] + re[cur];
				cur = son[cur][1];
			}
		}
	}
	//返回根节点元素
	T Rt() { return tree[rt]; };
	//返回x节点元素
	T fun(int x) { return tree[x]; };
	//返回根节点编号
	int return_root() { return rt; };
private:
	T tree[N] = { 0 };
	int sz = 0;
	int rt = 0;
	int f[N] = { 0 };
	int re[N] = { 0 };
	int rec[N] = { 0 };
	int son[N][2] = { 0 };
	int size[N] = { 0 };
	//获取x是其父亲的哪个儿子
	int getf(int x) {
		return son[f[x]][1] == x;
	}
	//清空x节点
	void clear(int x) {
		son[x][1] = son[x][0] = f[x] = size[x] = re[x] = 0;
	}
	//更新x节点的信息
	void update(int x) {
		size[x] = re[x] + size[son[x][0]] + size[son[x][1]];
	}
	//上旋编号为x的节点
	void rotate(int x) {
		int fa = f[x], ga = f[fa], t = getf(x), gs = son[x][t ^ 1];
		son[ga][getf(fa)] = x;
		f[x] = ga;
		son[fa][t] = gs;
		f[gs] = fa;
		son[x][t ^ 1] = fa;
		f[fa] = x;
		update(fa);
		update(x);
	}
	//旋转x节点到root
	void splay(int x, int root = 0) {
		while (f[x]!=root) {
			if (f[f[x]] != root) {
				if (getf(x) == getf(f[x]))
					rotate(f[x]), rotate(x);
				else
					rotate(x);
			}
			else 
				rotate(x);
		}
		if (!root)
			rt = x;
	}
};