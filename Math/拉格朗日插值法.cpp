//51nod 1258
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

int T;
long long n, k;
int f[100000];
int fac[100000];
int inv[100000];
int invk[100000];
int pre[100000];
int nextx[100000];
int up;
int ans;
const int M = 1e9 + 7;

int pow_mod(int x, int p)
{
	int tmp = x % M;
	int ans = 1;
	while (p)
	{
		if (p & 1)
		{
			ans = (long long)ans * tmp % M;
		}
		tmp = (long long)tmp * tmp % M;
		p >>= 1;
	}
	return ans;
}

int main()
{
	T = read();
	fac[0] = 1;
	for (int i = 1; i <= 50000 + 2; i++)
	{
		fac[i] = ((long long)fac[i - 1] * i) % M;
	}
	inv[0] = 1;
	inv[1] = 1;
	for (int i = 2; i <= 50000 + 2; i++)
	{
		inv[i] = (-(long long)inv[M % i] * (M / i) % M + M) % M;
	}
	invk[0] = 1;
	for (int i = 1; i <= 50000 + 2; i++)
	{
		invk[i] = (long long)invk[i - 1] * inv[i] % M;
	}
	while (T--)
	{
		n = read();
		n = n % M;
		k = read();
		for (int i = 1; i <= k + 2; i++)
		{
			f[i] = f[i - 1] + pow_mod(i, k);
			f[i] -= f[i] >= M ? M : 0;
		}
		if (n <= k + 2)
		{
			printf("%d\n", f[n]);
			continue;
		}
		up = 1;
		ans = 0;
		for (int i = 0; i <= k + 2; i++)
		{
			up = ((long long)up * ((n - i) % M)) % M;
		}
		pre[0] = 1;
		for (int i = 1; i <= k + 2; i++)
		{
			pre[i] = (long long)pre[i - 1] * (n - i) % M;
		}
		nextx[k + 3] = 1;
		for (int i = k + 2; i >= 0; i--)
		{
			nextx[i] = (long long)nextx[i + 1] * (n - i) % M;
		}
		for (int i = 1; i <= k + 2; i++)
		{
			int inv = (long long)invk[i - 1] * invk[k - i + 2] % M;
			int sign = ((k - i + 2) & 1) ? -1 : 1;
			ans += (long long)sign * inv % M * f[i] % M * pre[i - 1] % M * nextx[i + 1] % M;
			ans -= ans >= M ? M : 0;
			ans += ans <= -M ? M : 0;
		}
		ans = (ans + M) % M;
		printf("%d\n", ans);
	}
	return 0;
}
