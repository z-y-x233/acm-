struct edge
{
	int u, v, w;
	bool operator <(const edge & r) const {
		return w < r.w;
	}
};
struct kruskal
{
	int mspt(int n, vector<edge>& e) {
		sort(e.begin(), e.end());
		vector<int> f(n + 1);
		for (int i = 1; i <= n; ++i) f[i] = i;
		function<int(int)> find = [&](int x) -> int{
			return x == f[x] ? x : f[x] = find(f[x]);
		};
		int sum = 0, tag = n;
		for (auto &edge : e) {
			int u = edge.u;
			int v = edge.v;
			int w = edge.w;
			if (find(u) == find(v)) continue;
			f[find(u)] = find(v);
			sum += w;
			tag--;
		}
		if (tag > 1) sum = -1;
		return sum;
	}
}ks;