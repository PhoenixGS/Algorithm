void add(int c)
{
	knum++;
	int u = last;
	int v = knum;
	last = v;
	len[v] = len[u] + 1;
	for (; u && ! to[u][c]; u = pre[u])
	{
		to[u][c] = v;
	}
	if (! u)
	{
		pre[v] = root;
		return;
	}
	int w = to[u][c];
	if (len[u] + 1 == len[w])
	{
		pre[v] = w;
		return;
	}
	knum++;
	int neww = knum;
	pre[neww] = pre[w];
	len[neww] = len[w];
	for (int i = 0; i < 26; i++)
	{
		to[neww][i] = to[w][i];
	}
	pre[w] = pre[v] = neww;
	len[neww] = len[u] + 1;
	for (; u && to[u][c] == w; u = pre[u])
	{
		to[u][c] = neww;
	}
}
