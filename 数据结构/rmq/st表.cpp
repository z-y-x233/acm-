ll f[N][60];
int n, m;
void ini() {
    for (int j = 1; 1 << j <= n; ++j) {
        for (int i = 1; (1 << j) + i - 1 <= n; ++i) {
            f[i][j] = max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
        }        
    }
}

ll query(int l, int r) {
    int k = log2(r - l + 1);
    return max(f[l][k], f[r + 1 - (1 << k)][k]);
}