struct Tarjan
{
	struct edge
	{
		int v, to;
	}e[N];
	int h[N], cnt;
	void add(int u, int v) {
		e[cnt] = { v, h[u] };
		h[u] = cnt++;
	}

	//dcc[i]: 第i个点双连通分量中的点
	int dfn[N], low[N], st[N], top, num, rt, tot;
	vector<int> dcc[N];
	bool cut[N];
	void tarjan(int u) {
		dfn[u] = low[u] = ++num;
		st[++top] = u;
		if (u == rt && h[u] == -1) {
			dcc[++tot].push_back(u);
			return;
		}
		int f = 0;
		for (int i = h[u]; ~i; i = e[i].to) {
			int v = e[i].v;
			if (!dfn[v]) {
				tarjan(v);
				low[u] = min(low[u], low[v]);
				if (dfn[u] <= low[v]) {
					f++;
					tot++;
					int v2;
					if (u != rt || f > 1) cut[u] = 1;
					/**************
					求点双连通分量, 终止条件为v2 != v， 因为u可能属于多个点双连通分量
					****************/
					do {
						v2 = st[top--];
						dcc[tot].push_back(v2);
					} while (v2 != v);
					dcc[tot].push_back(u);
					/******************************/

				}
			}
			else
				low[u] = min(low[u], dfn[v]);
		}
	}



	
}tj;