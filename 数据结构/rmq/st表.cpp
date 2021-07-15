struct rmq
{
	//f[i][j]表示从i开始长度为2^j中的最值
	//初始化st表, n为原序列长度
	vector<vector<int>> f;
	rmq(){}
	rmq(int * a, int n) {
		init(a, n);
	}
	//a为原始序列
	void init(int *a, int n) {
		f.resize(n + 1);
		for (int i = 0; i <= n; ++i) {
			f[i].resize(40);
			f[i][0] = a[i];
		}
		for (int j = 1; 1 << j <= n; ++j) {
			for (int i = 1; (1 << j) + i - 1 <= n; ++i) {
				f[i][j] = max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
			}
		}
	}

	int query(int l, int r) {
		int k = log2(r - l + 1);
		return max(f[l][k], f[r + 1 - (1 << k)][k]);
	}
}rmq;
