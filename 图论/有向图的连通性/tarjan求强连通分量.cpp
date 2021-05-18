//tarjan缩点 强连通分量
//图不一定连通

//有向图和无向图的low[u]定义不同
//有向图为u出发能到达的最早出现的时间戳
//无向图为min(u的子树中的结点的时间戳, u通过不在生成树上的边到达的结点的时间戳)
struct Tarjan
{
	//邻接表存图部分
	//********************************************************//
	struct edge
	{
		int v, to;
	}e[N];
	int h[N], cnt;
	void add(int u, int v) {
		e[cnt] = {v, h[u]};
		h[u] = cnt++;
	}
	//********************************************************//

	int dfn[N], low[N], ins[N], st[N], c[N];
	int top, num, tot;
	vector<int> scc[N];
	void tarjan(int u) {
		dfn[u] = low[u] = ++num;
		st[++top] = u;
		ins[u] = 1;
		for (int i = h[u]; ~i; i = e[i].to) {
			int v = e[i].v;
			if (!dfn[v]) {
				tarjan(v);
				low[u] = min(low[u], low[v]);
			}
			else if (ins[v]) {
				low[u] = min(low[u], dfn[v]);
			}
		}
		if (dfn[u] == low[u]) {
			int v; tot++;
			do {
				v = st[top--], ins[v] = 0;
				c[v] = tot; scc[tot].push_back(v);
			} while(u != v);
		}
	}
	//缩点之后建立的有向无环图
	vector<int> dag[N];
	int in[N], out[N];
	void Dag(int n) {
		for (int i = 1; i <= n; ++i) {
			vector<bool> vis(n + 1);
			for (int j = h[i]; ~j; j = e[j].to) {
				int v = e[j].v;
				if (c[i] != c[v] && !vis[c[v]]) {
					dag[c[i]].push_back(c[v]);
					in[c[v]]++;
					out[c[i]]++;
					vis[c[v]] = 1;
				}
			}
		}
	}
}tj;