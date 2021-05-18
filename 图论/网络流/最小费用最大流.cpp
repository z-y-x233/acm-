
struct Dinic
{
	struct edge
	{
		int v, c, w, to;
	} e[N];
	int h[N], cnt;
	void add(int u, int v, int c, int w) {
		e[cnt] = { v, c, w, h[u] };
		h[u] = cnt++;
	}
	void ini() {
		memset(h, -1, sizeof h);
		cnt = 0;
	}
	Dinic() { ini(); }
	/************邻接矩阵部分****************************************/
	//点数, 源点, 汇点
	int n, s, t;
	void set(int n, int s, int t) {
		this->n = n;
		this->s = s;
		this->t = t;
	}
	//分层
	int dep[N], now[N];
	bool bfs() {
		for (int i = 1; i <= n; ++i) dep[i] = inf, now[i] = h[i];
		queue<int> q;
		bitset<N> st;
		dep[t] = 0, st[t] = 1;
		q.push(t);
		while (q.size()) {
			int u = q.front();
			q.pop();
			st[u] = 0;
			for (int i = h[u]; ~i; i = e[i].to) {
				int v = e[i].v, w = e[i ^ 1].w, c = e[i ^ 1].c;
				if (dep[u] + w < dep[v] && c) {
					dep[v] = dep[u] + w;
					if (!st[v]) q.push(v), st[v] = 1;
				}
			}
		}
		return dep[s] != inf;
	}
	bitset<N> vis;
	int cost;
	int dfs(int u, int in_flow = inf) {
		if (u == t) return in_flow;
		vis[u] = 1;
		int rest = in_flow;
		for (int i = now[u]; ~i && rest; i = e[i].to) {
			int v = e[i].v, w = e[i].w, c = e[i].c;
			now[u] = i;
			if (!vis[v] && dep[v] == dep[u] - w && c) {
				int res = dfs(v, min(c, rest));
				//记录已增广完成的点
				//若res=0, 则从v出发已不可能到达汇点
				if (!res) dep[v] = inf;
				else e[i].c -= res, e[i ^ 1].c += res, rest -= res, cost += res * w;
			}
		}
		vis[u] = 0;
		return in_flow - rest;
	}
	int maxflow() {
		int maxflow = 0, flow;
		while (bfs()) {
			while(flow = dfs(s)) maxflow += flow;

		}
		return maxflow;
	}
} dic;