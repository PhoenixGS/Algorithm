void Tarjan(int u, int father)
{
	times++;
	dfn[u] = low[u] = times;
	top++;
	stack[top] = u;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (! dfn[v])
		{
			Tarjan(v, u);
			if (low[v] >= dfn[u])
			{
				knumber++;
				points[knumber].push_back(u);
				belong[u].push_back(knumber);
				int tmp;
				do
				{
					tmp = stack[top];
					points[knumber].push_back(tmp);
					belong[tmp].push_back(knumber);
				}while(tmp != v);
			}
			low[u] = std::min(low[u], low[v]);
		}
		else
		{
			low[u] = std::min(low[u], dfn[v]);
		}
	}
}
