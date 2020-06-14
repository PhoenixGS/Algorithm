bool findc(int u, int father, int pre)
{
	vis[u] = 1;
	top++;
	stack[top] = u;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		int cost = val[i];
		if ((pre ^ i) != 1)
		{
			stac[top] = cost;
			if (vis[v])
			{
				last = 0;
				for (int k = top; k >= 1 && stack[k] != v; k--)
				{
					ff[stack[k]] = 1;
					last++;
					vv[last] = stack[k];
					ss[last] = stac[k - 1];
				}
				ff[v] = 1;
				last++;
				vv[last] = v;
				ss[last] = cost;
				return true;
			}
			else
			{
				if (findc(v, u, i))
				{
					return true;
				}
			}
		}
	}
	top--;
	return false;
}

