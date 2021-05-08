#include <bits/stdc++.h>
#include <unordered_map>

using namespace std;

const int N = 2e6 + 100;
#define IO std::ios::sync_with_stdio(false);std::cin.tie(0);std::cout.tie(0)


//求从源点出发到v的最短路有多少条
//ans[i]为到i点的最短路条数
//在dij更新最短路的时候若d[u] + w < d[v], 则ans[v] = ans[u]
//若d[u] + w == d[v], ans[v] += ans[u] 
struct edge
{
	int v, w, to;
}e[N];
int h[N], cnt = 1, ans[N], d[N];

//本题要去重, 好蠢
map<pair<int, int>, int> id;

void add(int u, int v, int w) {
	e[cnt] = {v, w, h[u]};
	h[u] = cnt++;
}




void ini() {
	memset(h, -1, sizeof h);
}

void dij(int u) {
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
	memset(d, 0x3f, sizeof d);
	d[u] = 0;
	ans[u] = 1;
	bitset<N> s;
	q.push({0, u});
	while(q.size()) {
		auto p = q.top();
		q.pop();
		int u = p.second;
		if (s[u]) continue;
		s[u] = 1;
		for (int i = h[u]; ~i; i = e[i].to) {
			int v = e[i].v, w = e[i].w;
			if (d[u] + w < d[v]) {
				d[v] = d[u] + w;
				ans[v] = ans[u];
				q.push({d[v], v});
			}
			else if (d[u] + w == d[v]) {
				ans[v] += ans[u];
			}
		}
	}	
}


signed main() {
	IO;
	ini();	
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= m; ++i) {
		int u, v, w;
		cin >> u >> v >> w;
		pair<int, int> p = {u, v};
		if (!id[p]) {
			id[p] = cnt;
			add(u, v, w);
		}
		else {
			e[id[p]].w = min(e[id[p]].w, w);
		}
		

	}
	dij(1);
	if (d[n] == 0x3f3f3f3f) cout << "No answer";
	else 
		cout << d[n] << ' ' << ans[n];
	return 0;
}
