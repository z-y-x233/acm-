struct Trie
{
	int t[N][27];
	int cnt[N];
	int idx;
	void insert(char* s) {
		int u = 0;
		for (int i = 1; s[i]; ++i) {
			int v = s[i] - 'a';
			if (!t[u][v]) t[u][v] = ++idx;
			u = t[u][v];
		}
		cnt[u]++;
	}

	int find(char* s) {
		int u = 0;
		for (int i = 1; s[i]; ++i) {
			int v = s[i] - 'a';
			if (!t[u][v]) return 0;
			u = t[u][v];
		}
		return cnt[u];
	}
}tr;