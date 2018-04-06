bool bfs()
{
	memset(dis, -1, sizeof(dis));
	int headx = 1;
	int tailx = 0;
	tailx++;
	que[tailx] = s;
	dis[s] = 0;
	while (headx <= tailx)
	{
		int u = que[headx];
		headx++;
		for (int i = head[u]; i; i = nextx[i])
		{
			int v = vet[i];
			int cost = val[i];
			if (cost && dis[v] == -1)
			{
				dis[v] = dis[u] + 1;
				tailx++;
				que[tailx] = v;
			}
		}
	}
	return dis[t] != -1;
}

int flow(int u, int maxflow)
{
	if (u == t)
	{
		return maxflow;
	}
	int ans = 0;
	for (int i = cur[u]; i; i = nextx[i])
	{
		int v = vet[i];
		int cost = val[i];
		if (dis[u] + 1 == dis[v])
		{
			int f = flow(v, std::min(maxflow - ans, cost));
			val[i] -= f;
			val[i ^ 1] += f;
			ans += f;
			cur[u] = i;
			if (ans == maxflow)
			{
				break;
			}
		}
	}
	if (ans < maxflow)
	{
		dis[u] = -1;
	}
	return ans;
}

long long maxflow()
{
	long long ans = 0;
	while (bfs())
	{
		for (int i = 1; i <= n + 2; i++)
		{
			cur[i] = head[i];
		}
		ans += flow(s, INF);
	}
	return ans;
}

