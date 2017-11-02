#include <cstdio>

int primenum;
int prime[1000000];
int n, m;
bool flag[10000000];

int main()
{
	primenum = 0;
	scanf("%d%d", &n, &m);
	flag[1] = true;
	for (int i = 2; i <= n; i++)
	{
		if (! flag[i])
		{
			primenum++;
			prime[primenum] = i;
		}
		for (int j = 1; j <= primenum && i * prime[j] <= n; j++)
		{
			flag[i * prime[j]] = true;
			if (i % prime[j] == 0)
			{
				break;
			}
		}
	}
	for (int i = 1; i <= m; i++)
	{
		int x;
		scanf("%d", &x);
		puts(flag[x] ? "No" : "Yes");
	}
	return 0;
}
