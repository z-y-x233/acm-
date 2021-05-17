struct Color
{
	struct edge
	{
		int v, to;
	}e[N];
	int h[N], cnt, col[N];
	int n;
	void add(int u, int v) {
		e[cnt] = {v, h[u]};
		h[u] = cnt++;
	}
	
	bool dfs(int u, int c) {
		col[u] = c;
		for (int i = h[u]; ~i; i = e[i].to) {
			int v = e[i].v;
			if (col[v] == c || (!col[v] && !dfs(v, 3 - c))) return false;
		}
		return true;
	}

	bool solve() {
		for (int i = 1; i <= n; ++i) {
			if (!col[i] && !dfs(i, 1)) return false;
		}
		return true;
	}

}cl;