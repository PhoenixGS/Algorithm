bool comp(int x, int y)
{
	return dfn[x] < dfn[y];
}

void dfs(int u, int father)
{
	times++;
	dfn[u] = times;
	fa[u][0] = father;
	for (int i = 1; i <= 20; i++)
	{
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
	}
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		long long cost = val[i];
		if (v != father)
		{
			//
			deep[v] = deep[u] + 1;
			dfs(v, u);
		}
	}
}

int querylca(int x, int y)
{
	if (deep[x] > deep[y])
	{
		std::swap(x, y);
	}
	for (int i = 20; i >= 0; i--)
	{
		if ((1 << i) & (deep[y] - deep[x]))
		{
			y = fa[y][i];
		}
	}
	if (x == y)
	{
		return x;
	}
	for (int i = 20; i >= 0; i--)
	{
		if (fa[x][i] != fa[y][i])
		{
			x = fa[x][i];
			y = fa[y][i];
		}
	}
	return fa[x][0];
}

void solve(int u, int father)
{
	//
}

int main()
{
	//input

	dfs(1, 0);

	edgenum = 0;
	for (int i = 1; i <= n; i++)
	{
		head[i] = 0;
	}

	scanf("%d", &m);
	while (m--)
	{
		int cnt = read();
		for (int i = 1; i <= cnt; i++)
		{
			x[i] = read();
			flag[x[i]] = 1;
		}
		cnt++;
		x[cnt] = 1;
		std::sort(x + 1, x + cnt + 1, comp);
		cnt = std::unique(x + 1, x + cnt + 1) - x - 1;
		for (int i = 1, tmp = cnt; i < tmp; i++)
		{
			cnt++;
			x[cnt] = querylca(x[i], x[i + 1]);
		}
		std::sort(x + 1, x + cnt + 1, comp);
		cnt = std::unique(x + 1, x + cnt + 1) - x - 1;
		top = 1;
		stack[top] = x[1];
		for (int i = 2; i <= cnt; i++)
		{
			while (top > 0 && deep[stack[top]] > deep[querylca(stack[top], x[i])])
			{
				top--;
			}
			if (stack[top])
			{
				add(stack[top], x[i]);
			}
			top++;
			stack[top] = x[i];
		}

		//solve

		edgenum = 0;
		for (int i = 1; i <= cnt; i++)
		{
			flag[x[i]] = 0;
			head[x[i]] = 0;
		}
	}
	return 0;
}

