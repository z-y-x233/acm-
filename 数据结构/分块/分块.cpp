//a: 原数组, len: 块长, id[i]: i对应的块, s[i]: 第i块的数据, tag[i]:第i块的增量
int a[N], s[N], id[N], len, tag[N];

void Xor(int l, int r) {
	if (id[l] == id[r]) {
		for (int i = l; i <= r; ++i) {
			a[i] ^= 1;
			//单点修改注意修改s[i],并且要把tag[i]算上
			s[id[i]] += ((a[i] ^ tag[id[i]]) ? 1 : - 1);
		}
		return;
	}
	for (int i = l; id[i] == id[l]; ++i) a[i] ^= 1, s[id[i]] += ((a[i] ^ tag[id[i]]) ? 1 : - 1);
	for (int i = id[l] + 1; i < id[r]; ++i) tag[i] ^= 1, s[i] = len - s[i];
	for (int i = r; id[i] == id[r]; --i) a[i] ^= 1, s[id[i]] += ((a[i] ^ tag[id[i]]) ? 1 : - 1);
}

int query(int l, int r) {
	int res = 0;
	if (id[l] == id[r]) {
		for (int i = l; i <= r; ++i) res += (a[i] ^ tag[id[i]]);
		return res;
	}
	for (int i = l; id[i] == id[l]; ++i) res += (a[i] ^ tag[id[i]]);
	for (int i = id[l] + 1; i < id[r]; ++i) {
		res += s[i];
	}
	for (int i = r; id[i] == id[r]; --i) res += (a[i] ^ tag[id[i]]);
	return res;
}