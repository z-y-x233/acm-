struct Dinic
{
	struct edge
	{
		int v, w, to;
	} e[N];
	int h[N], cnt;
	void add(int u, int v, int w) {
		e[cnt] = { v, w, h[u] };
		h[u] = cnt++;
	}
	void ini() {
		memset(h, -1, sizeof h);
		cnt = 0;
	}
	Dinic() { ini(); }
	/************邻接矩阵部分****************************************/
	//点数, 边数, 源点, 汇点
	int n, m, s, t;
	//分层和当前弧优化
	int dep[N], now[N];

	void set(int n, int s, int t) {
		this->n = n;
		this->s = s;
		this->t = t;
	}
	bool bfs() {
		for (int i = 1; i <= n; ++i) dep[i] = 0, now[i] = h[i];
		queue<int> q;
		dep[t] = 1;
		q.push(t);
		while (q.size()) {
			int u = q.front();
			q.pop();
			if (u == s) return 1;
			for (int i = h[u]; ~i; i = e[i].to) {
				int v = e[i].v, w = e[i ^ 1].w;
				if (!dep[v] && w) {
					dep[v] = dep[u] + 1;
					q.push(v);
				}
			}
		}
		return 0;
	}

	int dfs(int u, int in_flow = inf) {
		if (u == t) return in_flow;
		int rest = in_flow;
		for (int i = now[u]; ~i && rest; i = e[i].to) {
			int v = e[i].v, w = e[i].w;
			now[u] = i;
			if (dep[v] == dep[u] - 1 && w) {
				int res = dfs(v, min(w, rest));
				//记录已增广完成的点
				//若res=0, 则从v出发已不可能到达汇点
				if (!res) dep[v] = 0;
				e[i].w -= res;
				e[i ^ 1].w += res;
				rest -= res;
			}
		}
		return in_flow - rest;
	}

	int maxFlow() {
		int maxflow = 0, flow;
		while (bfs()) {
			maxflow += dfs(s);
		}
		return maxflow;
	}
} dic;