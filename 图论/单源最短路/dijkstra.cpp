struct edge {
	int v;
	int w;
	int to;
} e[N];
int h[N], cnt, d[N];

void add(int u, int v, int w) {
	e[cnt] = (edge) {v, w, h[u]};
	h[u] = cnt++;
}

void ini() {
	memset(h, -1, sizeof h);
	memset(d, 0x3f, sizeof d);
}
struct dij {
	const static int N = 1e5 + 100;
	//传入三个数组，求以u为源点到其他点的最短路，结果保存在d数组中
	void dij(int* h, edge* e, int* d, int u) {
		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
		q.push({d[u] = 0, u});
		bitset<N> s;
		while (q.size()) {
			auto p = q.top();
			q.pop();
			int dis = p.first;
			int u = p.second;
			if (s[u]) continue;
			s[u] = 1;
			for (int i = h[u]; ~i; i = e[i].to) {
				int v = e[i].v;
				int w = e[i].w;
				if (d[u] + w < d[v]) {
					d[v] = d[u] + w;
					q.push({d[v], v});
				}
			}
		}
	}
} dij;