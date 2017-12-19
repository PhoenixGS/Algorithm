#include <cstdio>
#include <algorithm>

int f[600000];
int size[600000];
int deep[600000];
int son[600000];
int top[600000];
int n, m, root;
int edgenum;
int vet[2000000];
int nextx[2000000];
int head[600000];

void add(int u, int v)
{
	edgenum++;
	vet[edgenum] = v;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

void dfs(int u, int father, int dep)
{
	f[u] = father;
	size[u] = 1;
	deep[u] = dep;
	son[u] = -1;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father)
		{
			dfs(v, u, dep + 1);
			size[u] += size[v];
			if (son[u] == -1 || size[v] > size[son[u]])
			{
				son[u] = v;
			}
		}
	}
}

void dfs2(int u, int chain)
{
	top[u] = chain;
	if (son[u] != -1)
	{
		dfs2(son[u], chain);
	}
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != f[u] && v != son[u])
		{
			dfs2(v, v);
		}
	}
}

int lca(int x, int y)
{
	while (top[x] != top[y])
	{
		if (deep[top[x]] < deep[top[y]])
		{
			std::swap(x, y);
		}
		x = f[top[x]];
	}
	if (deep[x] < deep[y])
	{
		return x;
	}
	else
	{
		return y;
	}
}

int main()
{
	edgenum = 0;
	scanf("%d%d%d", &n, &m, &root);
	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v);
		add(v, u);
	}
	dfs(root, 0, 0);
	dfs2(root, root);
	for (int i = 1; i <= m; i++)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		printf("%d\n", lca(x, y));
	}
	return 0;
}
