#include <cstdio>

int n, m;
int f[20000];
int rank[20000];

void makeset(int x)
{
	f[x] = x;
	rank[x] = 0;
}

int findfather(int x)
{
	return f[x] == x ? x : f[x] = findfather(f[x]);
}

void link(int x, int y)
{
	if (rank[x] > rank[y])
	{
		f[y] = x;
	}
	else
	{
		f[x] = y;
		if (rank[x] == rank[y])
		{
			rank[y]++;
		}
	}
}

void unionx(int x, int y)
{
	int xx = findfather(x);
	int yy = findfather(y);
	if (xx != yy)
	{
		link(xx, yy);
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		makeset(i);
	}
	for (int i = 1; i <= m; i++)
	{
		int cas, x, y;
		scanf("%d%d%d", &cas, &x, &y);
		if (cas == 1)
		{
			unionx(x, y);
		}
		else
		{
			printf("%c\n", findfather(x) == findfather(y) ? 'Y' : 'N');
		}
	}
	return 0;
}
