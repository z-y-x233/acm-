
int n, m, rt;
vector<int> g[N];
int fa[N][50], dep[N];
//fa[i][j]表示点i网上2^j长度的祖先
void dfs(int u, int f) {
    fa[u][0] = f;dep[u] = dep[f] + 1;
    for (int i = 1; (1 << i) <= dep[u]; ++i) {
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
    }
    for (auto v : g[u]) {
        if (v != f)
            dfs(v, u);
    }
}

int lca(int u, int v) {
    if (dep[u] < dep[v])
        swap(u, v);
    while(dep[u] > dep[v]) {
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
