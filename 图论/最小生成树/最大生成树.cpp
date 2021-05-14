#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
typedef long long ll;
typedef unsigned int ui;
typedef unsigned long long ull;

const int N = 2e5 + 100;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
//mt19937 rd(time(0));
#define IO std::ios::sync_with_stdio(false);std::cin.tie(0);std::cout.tie(0)

//给出一个图中任意两点
//让两点间所有路径中边权最小值最大化
//生成一颗最大生成树(反向排序即可), u和v之间的最小边权即为答案
struct edge
{
	int u, v, w;
	bool operator <(const edge & o) const {
		return w > o.w;
	}
};

vector<edge> e;
vector<pair<int, int>> g[N];
int urt[N], f[N];

int find(int x) { return x == f[x] ? x : f[x] = find(f[x]); }

int dep[N], fa[N][40], imin[N][40];

void dfs(int u, int f, int w, int rt) {
	urt[u] = rt;
	fa[u][0] = f;
	imin[u][0] = w;
	dep[u] = dep[f] + 1;
	for (int i = 1; (1 << i) <= dep[u]; ++i) {
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
		imin[u][i] = min(imin[u][i - 1], imin[fa[u][i - 1]][i - 1]);
	}
	for (auto p : g[u]) {
		if (p.first != f)
			dfs(p.first, u, p.second, rt);
	}
}


int lca(int u, int v) {
	if (dep[u] < dep[v]) swap(u, v);
	int res = inf;
	for (int i = log2(dep[u] - dep[v]) + 1; i >= 0; --i) {
		if (dep[fa[u][i]] >= dep[v]) {
			res = min(res, imin[u][i]);
			u = fa[u][i];
		}
	}
	if (u == v) return res;
	for (int i = log2(dep[u]) + 1; i >= 0; --i) {
		if (fa[u][i] != fa[v][i]) {
			res = min(res, imin[u][i]);
			res = min(res, imin[v][i]);
			u = fa[u][i];
			v = fa[v][i];
		}
	}
	res = min(res, imin[u][0]);
	res = min(res, imin[v][0]);
	return res;
}

void qwq() {
	int n, m, q;
	cin >> n >> m;
	// memset(imin, 63, sizeof imin);
	for (int i = 1; i <= m; ++i) {
		int u, v, w;
		cin >> u >> v >> w;
		e.push_back({ u, v, w });
	}
	for (int i = 1; i <= n; ++i) f[i] = i;
	sort(e.begin(), e.end());
	for (int i = 0; i < e.size(); ++i) {
		int u = e[i].u;
		int v = e[i].v;
		int w = e[i].w;
		if (find(u) == find(v)) continue;
		g[u].push_back({ v, w });
		g[v].push_back({ u, w });
		f[find(u)] = find(v);
	}

	for (int i = 1; i <= n; ++i) {
		if (!urt[i]) {
			dfs(i, 0, 0, i);
		}
	}
	cin >> q;
	while (q--) {
		int u, v;
		cin >> u >> v;
		if (urt[u] != urt[v]) cout << "-1\n";
		else cout << lca(u, v) << "\n";
	}
}

signed main() {
	IO;
	int _ = 1;
	// cin >> _;
	while (_--) qwq();
	return 0;
}
