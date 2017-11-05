void Tarjan(int u, int father)
{
	times++;
	dfn[u] = times;
	low[u] = times;
	top++;
	stack[top] = u;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father)
		{
			if (! dfn[v])
			{
				Tarjan(v, u);
				low[u] = std::min(low[u], low[v]);
			}
			else
			{
				low[u] = std::min(low[u], dfn[v]);
			}
		}
	}
	if (dfn[u] == low[u])
	{
		knumber++;
		while (stack[top + 1] != u)
		{
			knum[stack[top]] = knumber;
			top--;
		}
	}
}
