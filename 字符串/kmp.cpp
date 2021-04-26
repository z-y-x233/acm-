#include <bits/stdc++.h>

const int N = 1e6 + 100;
const long long mod = 998244353;
typedef long long ll;
#define IO std::ios::sync_with_stdio(false);std::cin.tie(0);std::cout.tie(0)


int next[N];

char s[N], s2[N];
int n, m;
//next数组定义为以i结尾的最长公共前后缀，i从1开始
void getNext() {
    int i = 2, j = 1;
    next[0] = -1;
    while (i <= m) {
        if (!j || s2[i] == s2[j]) next[i++] = j++;
        else j = next[j - 1] + 1;
    }
}

signed main() {
    IO;
    std::cin >> s + 1;
    std::cin >> s2 + 1;
    n = strlen(s + 1);
    m = strlen(s2 + 1);
    getNext();
    for (int i = 1, j = 1; i <= n;) {
        if (!j || s[i] == s2[j]) i++, j++;
        else j = next[j - 1] + 1;
        if (j == m + 1) {
            std::cout << i - m << "\n";
            j = next[m] + 1;
        }
    }
    for (int i = 1; i <= m; ++i) std::cout << next[i] << ' ';
    return 0;
}