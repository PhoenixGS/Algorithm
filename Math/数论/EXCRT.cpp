#include <cstdio>

long long read()
{
	char last = '+', ch = getchar();
	while (ch < '0' || ch > '9') last = ch, ch = getchar();
	long long tmp = 0;
	while (ch >= '0' && ch <= '9') tmp = tmp * 10 + ch - 48, ch = getchar();
	if (last == '-') tmp = -tmp;
	return tmp;
}

int n;
long long a1, m1, a2, m2;

long long mul(long long a, long long b, long long M)
{
	a = (a % M + M) % M;
	b = (b % M + M) % M;
	long long ans = 0;
	long long tmp = a;
	while (b)
	{
		if (b & 1)
		{
			ans = (ans + tmp) % M;
		}
		tmp = (tmp + tmp) % M;
		b >>= 1;
	}
	return ans;
}

long long extend_gcd(long long a, long long &x, long long b, long long &y)
{
	if (b == 0)
	{
		x = 1;
		y = 0;
		return a;
	}
	long long d = extend_gcd(b, x, a % b, y);
	long long t = x;
	x = y;
	y = t - a / b * y;
	return d;
}

void solve()
{
	long long x, y;
	long long d = extend_gcd(m1, x, m2, y);
	long long lcm = m1 / d * m2;
	a1 = ((mul(mul((a2 - a1) / d, m1, lcm), x, lcm) + a1) % lcm + lcm) % lcm;
	m1 = lcm;
}

int main()
{
	n = read();
	m1 = read();
	a1 = read();
	for (int i = 2; i <= n; i++)
	{
		m2 = read();
		a2 = read();
		solve();
	}
	printf("%lld\n", a1);
	return 0;
}
