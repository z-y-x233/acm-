#include <bits/stdc++.h>

const int N = 1e6 + 100;
const long long mod = 998244353;
typedef long long ll;
#define IO std::ios::sync_with_stdio(false);std::cin.tie(0);std::cout.tie(0)
using namespace std;

int Next[N];

char s[N], s2[N];

//luogu P3357 https://www.luogu.com.cn/problem/P3375
class kmp {
public:
    //next数组定义为以i结尾的最长公共前后缀，i从1开始
    void getNext(char* s, int* next) {
        int i = 2, j = 1, m = strlen(s + 1);
        next[0] = -1;
        while (i <= m) {
            if (!j || s[i] == s[j]) next[i++] = j++;
            else j = next[j - 1] + 1;
        }
    }
    //在字符串s中查找s2, 返回一个vector, 存储s2在s1中出现的下标(从1开始)
    vector<int> find(char* s, char* s2, int* next) {
        int n = strlen(s + 1), m = strlen(s2 + 1);
        vector<int> res;
        for (int i = 1, j = 1; i <= n;) {
            if (!j || s[i] == s2[j]) i++, j++;
            else j = next[j - 1] + 1;
            if (j == m + 1) {
                res.push_back(i - m);
                j = next[m] + 1;
            }
        }
        return res;
    }
} kmp;
signed main() {
    IO;
    std::cin >> s + 1;
    std::cin >> s2 + 1;
    kmp.getNext(s2, Next);
    auto res = kmp.find(s, s2, Next);
    for (auto v : res)
        cout << v << '\n';
    int m = strlen(s2 + 1);
    for (int i = 1; i <= m; ++i) std::cout << Next[i] << ' ';
    return 0;
}