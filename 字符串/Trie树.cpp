struct Trie
{
	int tr[N][27];
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
		int cur = 0;
		for (int i = 1; s[i]; ++i) {
			if (!tr[cur].son[s[i] - 'a']) return 0;
			else cur = tr[cur].son[s[i] - 'a'];
		}
		return tr[cur].cnt;
	}
}tr;