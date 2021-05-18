struct Manacher
{
	//p[i]代表以i为中心的回文串一半的长度(包括#)
	int cnt = 1, p[N];
	char s[N], ss[N];
	void ini() {
		ss[0] = '^'; ss[1] = '#';
		int len = strlen(s + 1);
		for (int i = 1; i <= len; ++i) {
			ss[++cnt] = s[i];
			ss[++cnt] = '#';
		}
	}
	int get() {
		ini();
		int mid = 1, r = -1, res = 0;
		for (int i = 1; i <= cnt; ++i) {
			if (i < r) p[i] = min(p[2 * mid - i], r + 1 - i); //p[i]最少等于关于mid对称点的长度且不超过r
			while (ss[i + p[i]] == ss[i - p[i]]) ++p[i]; 
			if (p[i] + i > r) r = p[i] + i - 1, mid = i; //更新r和mid
			res = max(res, p[i]);
		}
		return res - 1;
	}
}mac;
