//Codeforces 600E
#include <cstdio>

const int _n = 100000 + 10;
int n;
int col[_n];
int edgenum;
int vet[2 * _n], nextx[2 * _n], head[_n];
int size[_n], son[_n];
int cnt[_n];
int maxx;
long long sum;
long long ans[_n];

void add(int u, int v)
{
	edgenum++;
	vet[edgenum] = v;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

void dfs(int u, int father)
{
	size[u] = 1;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father)
		{
			dfs(v, u);
			size[u] += size[v];
			if (size[v] > size[son[u]])
			{
				son[u] = v;
			}
		}
	}
}

void add(int u, int father, int delta, int exc)
{
	cnt[col[u]] += delta;
	if (cnt[col[u]] > maxx)
	{
		maxx = cnt[col[u]];
		sum = col[u];
	}
	else
	{
		if (cnt[col[u]] == maxx)
		{
			sum += col[u];
		}
	}
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father && v != exc)
		{
			add(v, u, delta, exc);
		}
	}
}

void solve(int u, int father, int cas)
{
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father && v != son[u])
		{
			solve(v, u, 0);
		}
	}
	if (son[u])
	{
		solve(son[u], u, 1);
	}
	add(u, father, 1, son[u]);
	ans[u] = sum;
	if (cas == 0)
	{
		add(u, father, -1, 0);
		maxx = 0;
		sum = 0;
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &col[i]);
	}
	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v);
		add(v, u);
	}
	dfs(1, 0);
	solve(1, 0, 1);
	for (int i = 1; i <= n; i++)
	{
		printf("%lld ", ans[i]);
	}
	puts("");
	return 0;
}

