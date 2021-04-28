
//pr[i] 代表第i + 1个素数, s[i]表示i的最小素因子, n代表范围
void eul(int* pr, int*s, int &cnt, int n) {
    s[1] = s[0] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!s[i]) pr[cnt++] = i, s[i] = i;
        for (int j = 0; pr[j] * i <= n; ++j) {
            s[i * pr[j]] = pr[j];
            if (i % pr[j] == 0) break;
        }
    }
}