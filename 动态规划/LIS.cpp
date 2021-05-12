#include<iostream>
#include<cstring>
using namespace std;

const int N = 1e5 + 100;

int a[N], d[N], L = 1;

int main() {
    memset(d, 63, sizeof d);
    int n ;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    d[1] = a[1]; d[0] = -1;
    for (int i = 2; i <= n; ++i) {
        int l = 0, r = L;
        int res = 0;
        //因为对于d数组，整个数组是严格单调递增的
        //若存在j > i ,并且 d[j] < d[i],那么d[j]这个上升序列的倒数第二个数一定比d[i]小，因为序列严格单调上升
        //d[i]就可被替换为更小的数
        while (l < r) {
            int mid = l + r + 1 >> 1;
            if (d[mid] < a[i]) {
                l = mid;
            }
            else r = mid - 1;
        }
        res = l;
        L = max(res + 1, L);
        d[res + 1] = a[i];
    }
    cout << L;
    return 0;
}