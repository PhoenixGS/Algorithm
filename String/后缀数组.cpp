#include <cstdio>
#include <cstring>
#include <algorithm>

int n;
int m;
int cnt[200000];
int f[200000];
char s[200000];
int x[200000];
int SA[200000];
int tp[200000];
int rank[200000];
int height[200000];

void RadixSort()
{
	for (int i = 0; i <= m; i++)
	{
		cnt[i] = 0;
	}
	for (int i = 1; i <= n; i++)
	{
		cnt[rank[tp[i]]]++;
	}
	for (int i = 1; i <= m; i++)
	{
		cnt[i] += cnt[i - 1];
	}
	for (int i = n; i >= 1; i--)
	{
		SA[cnt[rank[tp[i]]]--] = tp[i];
	}
}

int cmp(int *f, int x, int y, int w)
{
	return f[x] == f[y] && f[x + w] == f[y + w];
}

void Suffix()
{
	for (int i = 1; i <= n; i++)
	{
		rank[i] = x[i];
		tp[i] = i;
	}
	m = 127;
	RadixSort();
	for (int w = 1, p = 1, i; p < n; w <<= 1, m = p)
	{
		for (p = 0, i = n - w + 1; i <= n; i++)
		{
			p++;
			tp[p] = i;
		}
		for (int i = 1; i <= n; i++)
		{
			if (SA[i] > w)
			{
				p++;
				tp[p] = SA[i] - w;
			}
		}
		RadixSort();
		std::swap(rank, tp);
		rank[SA[1]] = p = 1;
		for (int i = 2; i <= n; i++)
		{
			rank[SA[i]] = cmp(tp, SA[i], SA[i - 1], w) ? p : ++p;
		}
	}
	int j, k = 0;
	for (int i = 1; i <= n; height[rank[i++]] = k)
	{
		for (k = k ? k - 1 : k, j = SA[rank[i] - 1]; x[i + k] == x[j + k]; k++);
	}
}

int main()
{
	scanf("%s", s + 1);
	n = strlen(s + 1);
	for (int i = 1; i <= n; i++)
	{
		x[i] = s[i];
	}
	Suffix();
	for (int i = 1; i <= n; i++)
	{
		printf("%d ", SA[i]);
	}
	puts("");
	for (int i = 2; i <= n; i++)
	{
		printf("%d ", height[i]);
	}
	puts("");
	return 0;
}
