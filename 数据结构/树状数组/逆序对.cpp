#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
typedef long long ll;
typedef unsigned int ui;
typedef unsigned long long ull;

const int N = 1e6 + 100;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
mt19937 rd(time(0));
#define IO std::ios::sync_with_stdio(false);std::cin.tie(0);std::cout.tie(0)

//s数组维护的是原序列
int s[N], a[N];
int n;
int lowbit(int x) {
	return x & -x;
}
//把第p个数加x
void add(int p, int x) {
	while(p <= n) s[p] += x, p += lowbit(p);
}
//求前p项和
int sum(int p) {
	int res = 0;
	while(p) res += s[p], p -= lowbit(p);	
	return res;
}

int query(int l, int r) {
	return sum(r) - sum(l - 1);
}

std::vector<int> v;
int find(int x) {
	auto p = lower_bound(v.begin(), v.end(), x) - v.begin() + 1;
	return p;	
}

void qwq() {
	int m, x;
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		v.push_back(a[i]);
	}
	sort(v.begin(), v.end());
	ll res = 0;
	//树状数组求逆序对维护的是值域
	//每次查找前i个数中小于等于a[i]的数有x个
	//逆序的数量即为i - x
	for (int i = 1; i <= n; ++i) {
		add(find(a[i]), 1);
		int x = find(a[i]);
		res += i - sum(find(a[i]));
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