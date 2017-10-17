bool find(int u)
{
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (! flag[v])
		{
			flag[v] = true;
			if (match[v] == -1 || find(mathc[v]))
			{
				match[v] = u;
				return true;
			}
		}
	}
	return false;
}

int hungary()
{
	memset(match, -1, sizeof(match));
	int ans = 0;
	for (int i = 1; i <= n; i++)
	{
		memset(flag, 0, sizeof(flag));
		ans += find(i);
	}
	return ans;
}
