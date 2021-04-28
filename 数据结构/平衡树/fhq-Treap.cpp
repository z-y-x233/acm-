#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 100;
const long long mod = 998244353;
typedef long long ll;
mt19937 rd(time(0));
#define IO std::ios::sync_with_stdio(false);std::cin.tie(0);std::cout.tie(0)

struct treap
{
    int t[N][2];
    int e[N], r[N];
    int sz[N], rt, cnt;
    void update(int x) {
        sz[x] = sz[t[x][0]] + sz[t[x][1]] + 1;
    }
    void split(int root, int k, int &x, int &y) {
        if (!root) {
            x = y = 0;
            return;
        }
        if (e[root] <= k) {
            x = root;
            split(t[x][1], k, t[x][1], y);
        }
        else {
            y = root;
            split(t[y][0], k, x, t[y][0]);
        }
        update(root);
    }
    int merge(int x, int y) {
        if (!x || !y) return x + y;
        if (r[x] < r[y]) {
            t[x][1] = merge(t[x][1], y);
            update(x);
            return x;
        }
        else {
            t[y][0] = merge(x, t[y][0]);
            update(y);
            return y;
        }
    }
    int creat(int x) {
        e[++cnt] = x;
        r[cnt] = (ull)rd() * 114514 % 19491001;
        sz[cnt] = 1;
        return cnt;
    }
    void insert(int x) {
        int l, r;
        split(rt, x, l, r);
        rt = merge(merge(l, creat(x)), r);
    }
//返回第k个数的下标, 获取值e[kth()]
    int kth(int root, int k) {
        int u = root;
        while (true) {
            if (k <= sz[t[u][0]])
                u = t[u][0];
            else if (k - sz[t[u][0]] == 1) {
                return u;
            }
            else {
                k -= sz[t[u][0]] + 1;
                u = t[u][1];
            }
        }
    }
    int pre(int x) {
        int l, r;
        split(rt, x - 1, l, r);
        int k = kth(l, sz[l]);
        rt = merge(l, r);
        return e[k];
    }
    int suf(int x) {
        int l, r;
        split(rt, x, l, r);
        int k = kth(r, 1);
        rt = merge(l, r);
        return e[k];
    }
    void del(int x) {
        int l, r, k;
        split(rt, x, l, k);
        split(l, x - 1, l, r);
        r = merge(t[r][0], t[r][1]);
        rt = merge(merge(l, r), k);
    }
    int rak(int x) {
        int l, r;
        split(rt, x - 1, l, r);
        int ans = sz[l];
        rt = merge(l, r);
        return ans + 1;
    }

};
