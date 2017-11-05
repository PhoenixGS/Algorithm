void Tarjan(int u, int father)
{
	times++;
	dfn[u] = low[u] = times;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father)
		{
			if (! dfn[v])
			{
				Tarjan(v, u);
				low[u] = std::min(low[u], low[v]);
				if (low[v] > dfn[u])
				{
					addbridge(u, v);
				}
			}
			else
			{
				low[u] = std::min(low[u], dfn[v]);
			}
		}
	}
}
