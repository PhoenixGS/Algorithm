void dfs(int u, int father)
{
	times++;
	dfn[u] = times;
	pos[times] = u;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father)
		{
			deep[v] = deep[u] + 1;
			dfs(v, u);
			times++;
			pos[times] = u;
		}
	}
}

int query_lca(int x, int y)
{
	int l = dfn[x], r = dfn[y];
	if (l > r)
	{
		std::swap(l, r);
	}
	int k = z[r - l + 1];
	if (deep[st[l][k]] < deep[st[r - (1 << k) + 1][k]])
	{
		return st[l][k];
	}
	else
	{
		return st[r - (1 << k) + 1][k];
	}
}

int main()
{
	z[1] = 0;
	for (int i = 2; i <= 2 * n - 1; i++)
	{
		z[i] = z[i >> 1] + 1;
	}
	dfs(1, 0);
	for (int i = 1; i <= 2 * n - 1; i++)
	{
		st[i][0] = pos[i];
	}
	for (int j = 1; (1 << j) <= 2 * n - 1; j++)
	{
		for (int i = 1; i + (1 << j) <= 2 * n - 1; i++)
		{
			if (deep[st[i][j - 1]] < deep[st[i + (1 << (j - 1))][j - 1]])
			{
				st[i][j] = st[i][j - 1];
			}
			else
			{
				st[i][j] = st[i + (1 << (j - 1))][j - 1];
			}
		}
	}
}
