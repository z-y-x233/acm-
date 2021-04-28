
struct BIT
{
//s数组维护的是原序列
	int s[N];
	int n;
	int lowbit(int x) {
		return x & -x;
	}
//把第p个数加x
	void add(int p, int x) {
		while (p <= n) s[p] += x, p += lowbit(p);
	}
//求前p项和
	int sum(int p) {
		int res = 0;
		while (p) res += s[p], p -= lowbit(p);
		return res;
	}
	int query(int l, int r) {
		return sum(r) - sum(l - 1);
	}
};