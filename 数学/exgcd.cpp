//扩展欧几里得
ll exgcd(ll a,ll b,ll &x,ll &y) {
	if (!b) {
		x = 1; y = 0;
		return a;
	}
	ll d=exgcd(b, a%b, x, y);
	ll t = x;
	x = y;
	y = t - a / b * y;
	return d;
}

//求a在模p下的逆元
ll inv(ll a, ll p) {
	ll x, y;
	exgcd(a, p, x, y);
	x = x % p;
	if (x < 0) x += p;
	return x;
}
