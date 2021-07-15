#include <bits/stdc++.h>

using namespace std;
const int N = 1e6 + 10;
const int M = 40;
#define int long long
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))


//严格次小生成树模板题: https://www.luogu.com.cn/problem/P4180
//首先生成一颗最小生成树, 枚举所有未使用的边(u, v, w)
//求出u->v路径上严格小于w的最大边权w2, 次小生成树即为原值加上min(w - w2)
//树上倍增求u到v之间的次大边权 
struct edge
{
	int u, v, w;
	bool operator <(const edge & o) const { return w < o.w; };
};
vector<edge> e;

vector<pair<int, int>> g[N];

int f[N], n, m, fa[N][M], dep[N], imax[N][M], smax[N][M];
bool vis[N];
int find(int x) { return f[x] == x ? x : f[x] = find(f[x]); }

void dfs(int u, int f, int w) {
	fa[u][0] = f; dep[u] = dep[f] + 1;
	imax[u][0] = w; smax[u][0] = -1;
	for (int i = 1; (1 << i) <= dep[u]; ++i) {
		int tf = fa[u][i - 1];
		fa[u][i] = fa[tf][i - 1];
		imax[u][i] = max(imax[u][i - 1], imax[tf][i - 1]);
		smax[u][i] = max(smax[u][i - 1], smax[tf][i - 1]);
		if (imax[u][i - 1] != imax[tf][i - 1])
			smax[u][i] = max(smax[u][i], min(imax[u][i - 1], imax[tf][i - 1]));
	}
	for (auto p : g[u])
		if (p.first != f) dfs(p.first, u, p.second);
}

//求lca时对路径上所有的最大值和次大值一起更新
int lca(int u, int v, int w) {
	int dis1 = -1, dis2 = -1;
	if (dep[u] < dep[v])
		swap(u, v);
	std::function<void(int&, int&, int)> update = [&](int &dis1, int &dis2, int d){
		if (d > dis1) dis2 = dis1, dis1 = d;
		else if (d < dis1 && d > dis2) dis2 = d;
	};
	for (int i = (int)log2(dep[u] - dep[v]); i >= 0; --i) {
		if (dep[fa[u][i]] >= dep[v]) {
			update(dis1, dis2, imax[u][i]);
			update(dis1, dis2, smax[u][i]);
			u = fa[u][i];
		}
	}
	if (u != v) {
		for (int i = log2(dep[u]) + 1; i >= 0; --i) {
			if (fa[u][i] != fa[v][i]) {
				update(dis1, dis2, imax[u][i]);
				update(dis1, dis2, imax[v][i]);
				update(dis1, dis2, smax[u][i]);
				update(dis1, dis2, smax[v][i]);
				u = fa[u][i];
				v = fa[v][i];
			}
		}
		//把当前节点到lca的那条边更新
		update(dis1, dis2, imax[u][0]);
		update(dis1, dis2, imax[v][0]);
	}
	return dis1 != w ? dis1 : dis2;
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	
	for (int i = 1; i <= n; ++i) f[i] = i;
	for (int i = 1, u, v, w; i <= m; ++i) {
		cin >> u >> v >> w;
		e.push_back({ u, v, w });
	}
	sort(e.begin(), e.end());
	int sum = 0;
	for (int i = 0; i < e.size(); ++i) {
		int u = e[i].u, v = e[i].v, w = e[i].w;
		if (find(u) == find(v)) continue;
		g[u].push_back({ v, w });
		g[v].push_back({ u, w });
		vis[i] = 1;
		f[find(u)] = find(v);
		sum += w;
	}
	dfs(1, 0, 0);
	int res = 1e18;
	for (int i = 0; i < e.size(); ++i) {
		if (!vis[i]) {
			res = min(res, e[i].w - lca(e[i].u, e[i].v, e[i].w));
		}
	}
	cout << sum + res;
	return 0;
}