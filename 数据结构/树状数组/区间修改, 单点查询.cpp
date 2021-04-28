struct BIT
{
	//s数组维护的是读入序列的差分数组
//若要将区间[l, r]加上k, 即s[l] += k, s[r + 1] -= k;
//求第k个数即对差分数组求前k项和, 即为sum(k)
	int s[N];
	int n;
	int lowbit(int x) {
		return x & -x;
	}

	void add(int p, int x) {
		while (p <= n) s[p] += x, p += lowbit(p);
	}

	int sum(int p) {
		int res = 0;
		while (p) res += s[p], p -= lowbit(p);
		return res;
	}

	int query(int p) {
		return sum(p);
	}

//将区间[l, r]的所有数加上k
	void add(int l, int r, int k) {
		add(l, k);
		add(r + 1, -k);
	}
};