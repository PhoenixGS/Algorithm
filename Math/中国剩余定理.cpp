#include <cstdio>

int k;
long long a[10000];
long long n[10000];

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

long long calc(long long *a, long long *n, int k)
{
	long long a1 = a[0], n1 = n[0];
	for (int i = 1; i < k; i++)
	{
		long long a2 = a[i];
        long long n2 = n[i];
        long long x, y;
        long long d = extend_gcd(n1, x, n2, y);
		if ((a2 - a1) % d)
		{
			return -1;
		}
		long long lcm = n1 / d * n2;
		long long u0 = (a1 - a2) / d * x % (n2 / d);
		a1 = (a1 - u0 * n1) % lcm;
		n1 = lcm;
	}
	return (a1 % n1 + n1) % n1;
}

int main()
{
	scanf("%lld", &k);
	for (int i = 0; i < k; i++)
	{
		scanf("%lld%lld", &n[i], &a[i]);
	}
	printf("%lld\n", calc(a, n, k));
	return 0;
}