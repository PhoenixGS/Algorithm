void Tarjan(int u, int father)
{
	times++;
	dfn[u] = low[u] = times;
	int cnt = 0;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father)
		{
			if (! dfn[v])
			{
				cnt++;
				Tarjan(v, u);
				low[u] = std::min(low[u], low[v]);
				if (father != 0 && low[v] >= dfn[u])
				{
					cut[u] = true;
				}
			}
			else
			{
				low[u] = std::min(low[u], dfn[v]);
			}
		}
	}
	if (father == 0 && cnt > 1)
	{
		cut[u] = true;
	}
}
