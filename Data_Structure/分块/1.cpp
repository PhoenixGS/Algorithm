#include <cstdio>
#include <cmath>

long long read()
{
	char last = '+', ch = getchar();
	while (ch < '0' || ch > '9') last = ch, ch = getchar();
	long long tmp = 0;
	while (ch >= '0' && ch <= '9') tmp = tmp * 10 + ch - 48, ch = getchar();
	if (last == '-') tmp = -tmp;
	return tmp;
}

int n, m;
int x[10000];
int knumber;
int knum[10000];
int tag[100];

void update(int l, int r, int delta)
{
	if (knum[l] == knum[r])
	{
		for (int i = l; i <= r; i++)
		{
			x[i] += delta;
		}
		return;
	}
	for (int i = l; i <= knum[l] * knumber; i++)
	{
		x[i] += delta;
	}
	for (int i = (knum[r] - 1) * knumber + 1; i <= r; i++)
	{
		x[i] += delta;
	}
	for (int i = knum[l] + 1; i <= knum[r] - 1; i++)
	{
		tag[i] += delta;
	}
}

int main()
{
	n = read();
	for (int i = 1; i <= n; i++)
	{
		x[i] = read();
	}
	knumber = sqrt(n);
	for (int i = 1; i <= n; i++)
	{
		knum[i] = (i - 1) / knumber + 1;
	}
	m = read();
	for (int i = 1; i <= m; i++)
	{
		int cas = read();
		if (cas == 0)
		{
			int l, r, delta;
			l = read();
			r = read();
			delta = read();
			update(l, r, delta);
		}
		else
		{
			int pos = read();
			printf("%d\n", x[pos] + tag[knum[pos]]);
		}
	}
	return 0;
}
