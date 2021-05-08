#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
typedef long long ll;
typedef unsigned int ui;
typedef unsigned long long ull;

const int N = 2e3 + 100;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
//mt19937 rd(time(0));
#define IO std::ios::sync_with_stdio(false);std::cin.tie(0);std::cout.tie(0)

struct edge
{
	int v, w, l, to;
}e[N * N];
int h[N];
double t[200][N];
#define end End
int cnt, n, m, end;
double d[N][N];
pair<int, int> la[N][N];
void add(int u, int v, int w, int l) {
	e[cnt] = { v, w, l, h[u] };
	h[u] = cnt++;
}

struct node
{
	double t;
	int v, u;
	bool operator <(const node & o) const {
		return t > o.t;
	}
};

bitset<N> s[N];

void print(int u, int sp) {
	if (u == -1) 
		return;
	print(la[u][sp].first, la[u][sp].second);
	cout << u << ' ';
}


//例题: https://www.luogu.com.cn/problem/P1266
//每条道路的速度可变
//当权值可选时增加一维表示状态
//到若u -> v -> end 到v时的时间可不为最小值, 而到v的速度可以很大
//d[i][j] 表示为到点i且速度为j时的最短时间
//la[u][v]: 到达u且速度为v的最短时间走法的上一个状态的u, v
void dij() {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < N; ++j)
			d[i][j] = 1e18;
	}
	d[0][70] = 0;
	la[0][70] = {-1, -1};
	priority_queue<node> q;
	q.push({0, 70, 0});
	while(q.size()) {
		auto p = q.top();
		q.pop();
		int u = p.u;
		int sp = p.v;
		if (s[u][sp]) continue;
		s[u][sp] = 1;
		for (int i = h[u]; ~i; i = e[i].to) {
			int v = e[i].v;
			int cv = e[i].w ? e[i].w : sp;
			int l = e[i].l;
			if (d[v][cv] > d[u][sp] + 1.0 * l / cv) {
				d[v][cv] = d[u][sp] + 1.0 * l / cv;
				la[v][cv] = {u, sp};
				q.push({d[v][cv], cv, v});
			}			
		}
	}
	int mini = 0;
	for (int i = 0; i < N; ++i)
		if (d[end][mini] > d[end][i]) mini = i;
	print(end, mini);
}


void qwq() {
	memset(h, -1, sizeof h);
	cin >> n >> m >> end;
	for (int i = 1; i <= m; ++i) {
		int u, v, w, l;
		cin >> u >> v >> w >> l;
		add(u, v, w, l);
	}
	dij();

}

signed main() {
	IO;
	int _ = 1;
	// cin >> _;
	while (_--) qwq();
	return 0;
}
