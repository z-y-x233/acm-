#include <bitset/stdc++.h>

using namespace std;

const int V = 1e7;
const int N = 1e5;

int dp[v], v[N], w[N];

for (int i = 1; i <= n; ++i)
	for(int j = V; j >= v[i]; --j)
		f[j] = max(f[j], f[j - v[i]] + w[i]);