void bfs(int S)
{
	for (int i = 0; i <= n; i++)
	{
		slack[i] = INF;
		pre[i] = 0;
		vis[i] = 0;
	}
	int u, nw, nt, d;
	match[u = 0] = S;
	do
	{
		nw = match[u];
		d = slack[0];
		vis[u] = 1;
		for (int v = 1; v <= n; v++)
		{
			if (! vis[v])
			{
				if (nl[nw] + nr[v] - map[nw][v] < slack[v])
				{
					slack[v] = nl[nw] + nr[v] - map[nw][v];
					pre[v] = u;
				}
				if (slack[v] < d)
				{
					d = slack[v];
					nt = v;
				}
			}
		}
		for (int i = 0; i <= n; i++)
		{
			if (vis[i])
			{
				nl[match[i]] -= d;
				nr[i] += d;
			}
			else
			{
				slack[i] -= d;
			}
		}
	}while (match[u]);
	while (u)
	{
		match[u] = match[pre[u]];
		u = pre[u];
	}
}
