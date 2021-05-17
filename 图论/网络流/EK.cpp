struct EK
{
	struct edge
	{
		int v, w, to;
	}e[N];
	int h[N], cnt;
	void add(int u, int v, int w) {
		e[cnt] = {v, w, h[u]};
		h[u] = cnt++;
	}
	void ini() {
		memset(h, -1, sizeof h);
		cnt = 0;
	}

	EK() { ini(); };
	//pre[u]: 到达u的边的编号, d[u]:到达u点的最小流量
	int pre[N], d[N];
	int n, m, s, t;
	int bfs() {
		int flow = inf;
		queue<int> q;
		bitset<N> st;
		st[s] = 1;
		d[s] = inf;
		q.push(s);
		while(q.size()) {
			int u = q.front();
			q.pop();
			if (u == t) return 1;
			for (int i = h[u]; ~i; i = e[i].to) {
				int v = e[i].v, w = e[i].w;
				if (!st[v] && w) {
					d[v] = min(d[u], w);
					st[v] = 1;
					pre[v] = i;
					q.push(v);
				}
			}
		}
		return 0;
	}

	int update() {
		int u = t;
		while(u != s) {
			int i = pre[u];
			e[i].w -= d[t];
			e[i ^ 1].w += d[t];
			u = e[i ^ 1].v;
		}
		return d[t];
	}

	int maxFlow() {
		int maxflow = 0;
		while(bfs()) {
			maxflow += update();
		}
		return maxflow;
	}
}ek;