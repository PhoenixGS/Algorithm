#include <cstdio>
#include <cmath>
#include <algorithm>

const int _k = 66000;
int T;
long long n;
long long knum;
int flag[_k];
int last;
long long v[_k];
int primenum;
long long prime[_k], psum[_k];
long long ci[_k], mu[_k], de[_k], pmu[_k], pde[_k];
long long g[_k], fm[_k], fd[_k];
long long pos1[_k], pos2[_k];
long long ans;

void calc_prime(int n)
{
	primenum = 0;
	ci[1] = 0;
	mu[1] = 1;
	de[1] = 1;
	for (int i = 2; i <= n; i++)
	{
		if (! flag[i])
		{
			primenum++;
			prime[primenum] = i;
			psum[primenum] = psum[primenum - 1] + i;
			ci[i] = 1;
			mu[i] = -1;
			de[i] = 2;
		}
		for (int j = 1; j <= primenum && i * prime[j] <= n; j++)
		{
			flag[i * prime[j]] = 1;
			if (i % prime[j] == 0)
			{
				ci[i * prime[j]] = ci[i] + 1;
				mu[i * prime[j]] = 0;
				de[i * prime[j]] = de[i] / (ci[i] + 1) * (ci[i] + 2);
				break;
			}
			else
			{
				ci[i * prime[j]] = 1;
				mu[i * prime[j]] = -mu[i];
				de[i * prime[j]] = de[i] * 2;
			}
		}
	}
	for (int i = 1; i <= n; i++)
	{
		pmu[i] = pmu[i - 1] + mu[i];
		pde[i] = pde[i - 1] + (long long)de[i] * de[i];
	}
}

void query()
{
	for (int i = 1; i <= last; i++)
	{
		fm[i] = -g[i];
		fd[i] = 4ll * g[i];
	}
	for (int i = primenum; i >= 1; i--)
	{
		for (int j = 1; j <= last && prime[i] * prime[i] <= v[j]; j++)
		{
			for (long long e = 1, t = prime[i]; t * prime[i] <= v[j]; e++, t = t * prime[i])
			{
				int op = v[j] / t <= knum ? pos1[v[j] / t] : pos2[n / (v[j] / t)];
				long long tmpm = -i;
				long long tmpd = 4ll * i;
				fm[j] = fm[j] + (long long)(e == 1 ? -1 : 0) * (fm[op] - tmpm);
				fd[j] = fd[j] + (long long)(e + 1) * (e + 1) * (fd[op] - tmpd) + (long long)(e + 2) * (e + 2);
			}
		}
	}
}

int main()
{
	scanf("%d", &T);
	while (T--)
	{
		//init

		scanf("%lld", &n);
		knum = sqrt(n);
		calc_prime(knum);
		
		last = 0;
		for (long long i = 1, j; i <= n; i = j + 1)
		{
			j = n / (n / i);
			last++;
			v[last] = n / i;
			long long t = n / i;
			g[last] = t - 1;
			if (n / i <= knum)
			{
				pos1[n / i] = last;
			}
			else
			{
				pos2[n / (n / i)] = last;
			}
		}
		for (int i = 1; i <= primenum; i++)
		{
			for (int j = 1; j <= last && (long long)prime[i] * prime[i] <= v[j]; j++)
			{
				int op = v[j] / prime[i] <= knum ? pos1[v[j] / prime[i]] : pos2[n / (v[j] / prime[i])];
				g[j] = g[j] - (g[op] - (i - 1));
			}
		}
		query();
		ans = 0;
		for (int i = 1; i <= knum; i++)
		{
			int op = n / i <= knum ? pos1[n / i] : pos2[n / (n / i)];
			ans = ans + (long long)mu[i] * (fd[op] + 1);
			ans = ans + (long long)de[i] * de[i] * (fm[op] + 1);
		}
		ans = ans - (long long)pmu[knum] * pde[knum];
		printf("%lld\n", ans);
	}
	return 0;
}
