struct LCA
{
//g为邻接表存图
    vector<int> g[N];
//fa[i][j]表示点i网上2^j长度的祖先
    int fa[N][50], dep[N];
//dfs初始化父节点, 复杂度nlogn
    void dfs(int u, int f) {
        fa[u][0] = f; dep[u] = dep[f] + 1;
        for (int i = 1; (1 << i) <= dep[u]; ++i) {
            fa[u][i] = fa[fa[u][i - 1]][i - 1];
        }
        for (auto v : g[u]) {
            if (v != f)
                dfs(v, u);
        }
    }
//返回u和v的最近公共祖先
    int lca(int u, int v) {
        if (dep[u] < dep[v])
            swap(u, v);
        while (dep[u] > dep[v]) {
            u = fa[u][(int)log2(dep[u] - dep[v])];
        }
        if (u == v) return v;
        for (int i = log2(dep[u]) + 1; i >= 0; --i) {
            if (fa[u][i] != fa[v][i]) {
                u = fa[u][i];
                v = fa[v][i];
            }
        }
        return fa[u][0];
    }
};