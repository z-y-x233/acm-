struct maxMatch
{
	struct edge
	{
		int v, to;
	}e[N];
	int h[N], cnt;
	void add(int u, int v) {
		e[cnt] = {v, h[u]};
		h[u] = cnt++;
	}
	bitset<N> vis;
	int match[N];
	bool dfs(int u) {
		for (int i = h[u]; ~i; i = e[i].to) {
			int v = e[i].v;
			if (!vis[v]) {
				vis[v] = 1;
				if (match[v] || dfs(match[v])) {
					return vis[v] = 0, match[v] = u;
				}
			}
		}
		return false;
	}

	int solve() {
		int res = 0;
		for (int i = 1; i <= n; ++i) {
			if (dfs(i)) res++;
		}
		return res;
	}

}mt;