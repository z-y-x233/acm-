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
#define int ll

//模板: https://www.luogu.com.cn/problem/P5905
//带负权边的多源最短路 
//不能有负环
//建立超级源点0, 加n条边权为0的边连向其他点
//H[i]代表从0出发到各个点的最短路
//将原(u, w)的边权加上H[u] - H[v]
//此时从u出发跑一遍Dijkstra得到的d[v] + H[v] - H[u]就为u->v的最短路 

//原理
//更改边权后任意u->v的最短路为dis(u, v) + H[u] - H[v], 中间的H抵消
//又对任意u->v, H[v] <= H[u] + w(u, v)
//因此w(u, v) + H[u] - H[v] >= 0, 所有边权非负, 可以使用Dijkstra算法

struct edge {
	int v;
	int w;
	int to;
} e[N];
int h[N], cnt, d[N];

void add(int u, int v, int w) {
	e[cnt] = { v, w, h[u] };
	h[u] = cnt++;
}

void ini() {
	memset(h, -1, sizeof h);

}
struct dijk {
	const static int N = 1e5 + 100;
	//传入三个数组，求以u为源点到其他点的最短路，结果保存在d数组中
	void dij(int* h, edge* e, int* d, int u) {
		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
		for (int i = 1; i < N; ++i) d[i] = 1000000000;
		q.push({ d[u] = 0, u });
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
					q.push({ d[v], v });
				}
			}
		}
	}
} dij;


int H[N];

bool spfa(int n) {
	queue<int> q;
	q.push(0);
	memset(H, 0x3f, sizeof H);
	H[0] = 0;
	vector<int> cnt(n + 1);
	bitset<N> st;
	while (q.size()) {
		int u = q.front();
		q.pop();
		if (cnt[u] > n) return false;

		st[u] = 0;
		for (int i = h[u]; ~i; i = e[i].to) {
			int v = e[i].v;
			int w = e[i].w;
			if (H[u] + w < H[v]) {
				H[v] = H[u] + w;
				if (!st[v]) {
					q.push(v);
					st[v] = 1;
					cnt[v]++;
				}
			}
		}
	}
	return true;
}

void qwq() {
	ini();
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		add(0, i, 0);
	}
	for (int i = 1; i <= m; ++i) {
		int u, v, w;
		cin >> u >> v >> w;
		add(u, v, w);
	}
	if (!spfa(n)) cout << "-1";
	else {
		for (int i = 1; i <= n; ++i) {
			for (int j = h[i]; ~j; j = e[j].to) {
				e[j].w += H[i] - H[e[j].v];
			}
		}
		for (int i = 1; i <= n; ++i) {
			dij.dij(h, e, d, i);
			int res = 0;
			for (int j = 1; j <= n; ++j) {
				int dis = d[j];
				if (dis != 1000000000) dis += H[j] - H[i];
				res += dis * j;
				// cout << dis << " \n"[j == n];
			}
			cout << res << "\n";
		}
	}
}

signed main() {
	IO;
	int _ = 1;
	// cin >> _;
	while (_--) qwq();
	return 0;
}
