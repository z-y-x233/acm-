/*
AC自动机还经常与dp结合食用，套路一般为f[i][j]表示当前长度为i
在AC自动机上第j号节点时的答案，转移的时候枚举出边
*/
struct ACatm
{
	int tr[N][30];
	int cnt[N];
	int fail[N];
	int idx;

	void ini() {
		memset(tr, 0, sizeof tr);
		for (int i = 0; i <= idx; ++i) fail[i] = cnt[i] = 0;
		idx = 0;
	}
	void insert(char* s) {
		int u = 0;
		for (int i = 1; s[i]; ++i) {
			int v = s[i] - 'a';
			if (!tr[u][v]) tr[u][v] = ++idx;
			u = tr[u][v];
		}
		cnt[u]++;
	}
	//在一般的匹配问题中，我们会把trie树补为trie图，虽然这样会极大的降低匹配时间
	//但是当利用的fail树中各节点相对位置(例如lca)的时候不建议这么做
	void build() {
		queue<int> q;
		for (int i = 0; i < 26; ++i) {
			if (tr[0][i]) q.push(tr[0][i]);
		}
		while(q.size()) {
			int u = q.front();
			q.pop();
			/********************Trie树初始化**********************/
			//trie树
			// for (int i = 0; i < 26; ++i) {
			// 	if (tr[u][i]) {
			// 		int v = fail[u];
			// 		while(!tr[v][i] && v) v = fail[v];
			// 		fail[tr[u][i]] = tr[v][i];
			// 		q.push(tr[u][i]);
			// 	}
			// }

			/********************Trie图初始化**********************/
			for (int i = 0; i < 26; ++i) {
				if (tr[u][i]) 
					fail[tr[u][i]] = tr[fail[u]][i], q.push(tr[u][i]); 
				else 
					tr[u][i] = tr[fail[u]][i]; 
			} 
		}
	}
	//查询有多少模式串在s中出现过, 模式串不同当且仅当下边不同
	int query(char* s) {
		int u = 0, res = 0;
		for (int i = 1; s[i]; ++i) {
			/********************Trie树查询**********************/
			// int v = s[i] - 'a';
			// while(u && !tr[u][v]) u = fail[u];
			// if (tr[u][v]) u = tr[u][v];
			// if (~cnt[u]) res += cnt[u], cnt[u] = -1;

			/********************Trie图查询**********************/
			u = tr[u][s[i] - 'a'];
			for (int j = u; j && ~cnt[j]; j = fail[j]) {
				res += cnt[j];
				cnt[j] = -1;
			}
		}
		return res;
	}
}ac;