//tarjan求无向图割边
//图不一定连通

//有向图和无向图的low[u]定义不同
//有向图为u出发能到达的最早出现的时间戳
//无向图为min(u的子树中的结点的时间戳, u通过不在生成树上的边到达的结点的时间戳)
struct Tarjan
{
	struct edge
	{
		int v, to;
	} e[N];
	int h[N], cnt;

	void add(int u, int v) {
		e[cnt] = {v, h[u]};
		h[u] = cnt++;
	}

	int dfn[N], low[N], num, tot;
	
	bool bridge[N];

	void tarjan(int u, int edge) {
		dfn[u] = low[u] = ++num;
		for (int i = h[u]; ~i; i = e[i].to) {
			int v = e[i].v;
			if (!dfn[v]) {
				tarjan(v, i);
				low[u] = min(low[u], low[v]);
				if (dfn[u] < low[v]) {
					bridge[edge] = bridge[edge ^ 1] = 1;
				}
			}
			else if (i != (edge ^ 1)) {
				low[u] = min(low[u], dfn[v]);
			}
		}
	}

	/*
	 * 求边双联通分量, 求出割边后进行一次dfs, 即可求出所有边双联通分量
	 * dcc[i]: 第i个边双联通分量中的点
	 * c[i]: i对应的边双联通分量编号
	 * _sz: 边双联通分量编号
	 */
	vector<int> dcc;
	int c[N];
	int _sz;
	void dfs(int u) {
		c[u] = _sz;
		for (int i = h[u]; ~i; i = e[i].to) {
			int v = e[i].v;
			if (bridge[i] || c[v]) continue;
			dfs(v);
		}
	}

	void Dcc(int n) {
		dcc.resize(n + 1);
		for (int i = 1; i <= n; ++i) {
			if (!c[i]) {
				_sz++;
				dfs(i);
			}
		}
	}

};