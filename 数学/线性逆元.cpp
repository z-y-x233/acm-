
//线性求逆元

typedef  long long ll;
const int N = 2e5 + 5;
int inv[N];

//求1-n模p的逆元
void inverse(int n, int p) {
    inv[1] = 1;
    for (int i=2; i<=n; ++i) {
        inv[i] = (ll) (p - p / i) * inv[p%i] % p;
    }
}