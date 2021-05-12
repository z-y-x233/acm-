#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
typedef long long ll;
typedef unsigned int ui;
typedef unsigned long long ull;

const int N = 1e6 + 100;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
//mt19937 rd(time(0));
#define IO std::ios::sync_with_stdio(false);std::cin.tie(0);std::cout.tie(0)
#define int ll
namespace io {
	const int L = 10000000;
	char buf[L], *front=buf, *end=buf;
	char GetChar() {
		if (front == end) {
			end = buf + fread(front = buf, 1, L, stdin);
			if (front == end) return -1;
		}
		return *(front++);
	}

	template <typename T>
	void read(T &x) {
		x = 0;int w = 1;
		char c = 0, la = ' ';
		while(c > '9' || c < '0') la = c, c = GetChar();
		while(c >= '0' && c <= '9') x = x * 10 + c - 48, c = GetChar();
		if (la == '-') x = -x;
	}
	template <typename T>
	void write(T x) {
		int s[1000], top = 0;
		do {s[++top] = x % 10; x /= 10;} while(x);
		while(top) putchar(s[top--] + 48);
	}
}


struct edge
{
	int v, w, to;
}e[N];
int h[N], cnt, s, t, n, m, k;
int d[2][N];
int col[2][N];
void add(int u, int v, int w) {
	e[cnt] = { v, w, h[u] };
	h[u] = cnt++;
}

struct node
{
	int w, u;
	bool operator <(const node & r) const {
		return w > r.w;
	}
};

bitset<N> sp;
vector<int> kp;
vector<pair<pair<int, int>, int>> in;
void ini() {
	memset(h, -1, sizeof h);
	cnt = 0;
	sp &= 0;
	kp.clear();
	in.clear();
}
/* 求k个特殊点中任意两点的最短路的最小值
 * 因为这条路必须经过某条边, 考虑所有边(u, v, w)的贡献
 * 因为是有向图, 设d[0][u]为从特殊点到达u的最短距离, col[0][u]为离u最近的点
 * d[1][v]为从v出发到达特殊点的最短距离, col[1][v]反向离v最近的点
 * 若从u出发的点和v到达的点不同, 则这条路径的距离为d[0][u] + d[1][v] + w
 * 中间可能存在枚举最优路径u->v的中间边{x, y}时, y到u的距离和y到v的距离相同而跳过 
 * 但是对任意一条非环路径u->v, 一定可以通过u的出边和v的入边枚举到, 因此一定可以枚举出答案
 */
void dij(int *d, int * col) {
	bitset<N> st;
	priority_queue<node> q;
	for (int i = 1; i <= n; ++i) {
		if (sp[i]) {
			d[i] = 0;
			q.push({0, i});
			col[i] = i;
		}
		else 
			d[i] = 1e18, col[i] = 0;
	}
	while (q.size()) {
		auto p = q.top();
		q.pop();
		int u = p.u;
		if (st[u]) continue;
		st[u] = 1;
		for (int i = h[u]; ~i; i = e[i].to) {
			int v = e[i].v;
			int w = e[i].w;
			if (d[v] > d[u] + w) {
				d[v] = d[u] + w;
				col[v] = col[u];
				q.push({d[v], v});
			}
		}
	}
}


void qwq() {
	ini();
	io::read(n);io::read(m);io::read(k);
	for (int i = 1; i <= m; ++i) {
		int u, v, w;
		io::read(u);io::read(v);io::read(w);
		in.push_back({{u, v}, w});
		add(u, v, w);
	}
	for (int i = 1; i <= k; ++i) {
		int x;
		io::read(x);
		kp.push_back(x);
		sp[x] = 1;
	}
	dij(d[0], col[0]);

	memset(h, -1, sizeof h);
	cnt = 0;
	for (auto inp: in) {
		int u = inp.first.first;
		int v = inp.first.second;
		int w = inp.second;
		add(v, u, w);
	}
	dij(d[1], col[1]);
	int res = 1e18;
	for (auto inp: in) {
		int u = inp.first.first;
		int v = inp.first.second;
		int w = inp.second;
		if (col[0][u] && col[1][v] && col[0][u] != col[1][v]) 
			res = min(res, d[0][u] + d[1][v] + w); 
	}
	io::write(res);
	putchar('\n');
}

signed main() {
	// IO;
	int _ = 1;
	// cin >> _;
	io::read(_);
	while (_--) qwq();
	return 0;
}
