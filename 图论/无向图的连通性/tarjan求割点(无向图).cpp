//tarjan求无向图割点
//图不一定连通
//每次求一个图的割点时要设置root
//else是不要使用low[v]更新low[u]
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
	int dfn[N], low[N], num, tot, root;
	
	bitset<N> cut;
	void tarjan(int u) {
		dfn[u] = low[u] = ++num;
		int f = 0;
		for (int i = h[u]; ~i; i = e[i].to) {
			int v = e[i].v;
			if (!dfn[v]) {
				tarjan(v);
				low[u] = min(low[u], low[v]);
				if (dfn[u] <= low[v]) {
					f++;
					if (f > 1 || u != root) cut[u] = 1;
				}
			}
			else 
				low[u] = min(low[u], dfn[v]);
		}
	}
}tj;