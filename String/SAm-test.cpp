void add(int c)
{
	knum++;
	int u = last;
	int v = knum;
	last = knum;
	len[v] = len[u] + 1;
	for (; u && ! ch[u][c]; u = pre[u])
	{
		ch[u][c] = v;
	}
	if (! u)
	{
		pre[v] = 1;
		return;
	}
	int w = ch[u][c];
	if (len[u] + 1 == len[w])
	{
		pre[v] = w;
		return;
	}
	knum++;
	int neww = knum;
	len[neww] = len[u] + 1;
	pre[neww] = pre[w];
	pre[w] = pre[v] = neww;
	for (int i = 0; i < 26; i++)
	{
		ch[neww][i] = ch[w][i];
	}
	for (; u && ch[u][c] == w; u = pre[u])
	{
		ch[u][c] = neww;
	}
}
