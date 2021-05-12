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

struct edge
{
	int v, w, to;
}e[N];
int h[N], cnt, s, t, n, m, k;
int d[N][20];
void add(int u, int v, int w) {
	e[cnt] = { v, w, h[u] };
	h[u] = cnt++;
}

struct node
{
	int w, u, t;
	bool operator <(const node & r) const {
		return w > r.w;
	}
};

void ini() {
	memset(h, -1, sizeof h);
}


//题目可以选择k条边边权为零
//在路径上加一维状态代表免费路线条数, d[i][j]表示到i点并且使用j条免费路线的最短路
//状态转移时判断能否使用免费路线, 若能使用, 因为多使用了一条免费路线
//所以需要检查并更新d[i][j + 1]的状态
//在获取答案是枚举d[t][[0-k]], 因为不一定需要使用所有的免费路线, 或者有权值为0的情况
void dij() {
	memset(d, 0x3f, sizeof d);
	bitset<20> st[N];
	for (int i = 0; i <= k; ++i) d[s][i] = 0;
	priority_queue<node> q;
	q.push({ 0, s, 0 });
	while (q.size()) {
		auto p = q.top();
		q.pop();
		int u = p.u;
		int t = p.t;
		if (st[u][t]) continue;
		st[u][t] = 1;
		for (int i = h[u]; ~i; i = e[i].to) {
			int v = e[i].v;
			int w = e[i].w;
			if (d[v][t] > d[u][t] + w) {
				d[v][t] = d[u][t] + w;
				q.push({ d[v][t], v, t });
			}
			if (t < k && d[v][t + 1] > d[u][t]) {
				d[v][t + 1] = d[u][t];
				q.push({ d[v][t + 1], v, t + 1 });
			}
		}
	}
}


void qwq() {
	ini();
	cin >> n >> m >> k;
	cin >> s >> t;
	for (int i = 1; i <= m; ++i) {
		int u, v, w;
		cin >> u >> v >> w;
		add(u, v, w);
		add(v, u, w);
	}
	dij();
	int res = inf;
	for (int i = 0; i <= k; ++i) {
		res = min(res, d[t][i]);
	}
	cout << res;
}

signed main() {
	IO;
	int _ = 1;
	// cin >> _;
	while (_--) qwq();
	return 0;
}
