#include <cstdio>
#include <algorithm>

long long read()
{
	char last = '+', ch = getchar();
	while (ch < '0' || ch > '9') last = ch, ch = getchar();
	long long tmp = 0;
	while (ch >= '0' && ch <= '9') tmp = tmp * 10 + ch - 48, ch = getchar();
	if (last == '-') tmp = -tmp;
	return tmp;
}

const int INF = 1000000000;
const int _n = 800 + 10;
int n, nl, nr, m, map[_n][_n];
int slack[_n], sl[_n], sr[_n], pre[_n], match[_n];
bool vis[_n];
long long ans;

void bfs(int S)
{
	for (int i = 0; i <= n; i++)
	{
		slack[i] = INF;
		vis[i] = 0;
		pre[i] = 0;
	}
	int u, nt, d, nw;
	match[u = 0] = S;
	do
	{
		nw = match[u];
		d = slack[0];
		vis[u] = true;
		for (int v = 1; v <= n; v++)
		{
			if (! vis[v])
			{
				if (sl[nw] + sr[v] - map[nw][v] < slack[v])
				{
					slack[v] = sl[nw] + sr[v] - map[nw][v];
					pre[v] = u;
				}
				if (d > slack[v])
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
				sl[match[i]] -= d;
				sr[i] += d;
			}
			else
			{
				slack[i] -= d;
			}
		}
		u = nt;
	}while (match[u]);
	while(u)
	{
		match[u] = match[pre[u]];
		u = pre[u];
	}
}

int main()
{
	scanf("%d%d%d", &nl, &nr, &m);
	n = std::max(nl, nr) << 1;
	for (int i = 1; i <= m; i++)
	{
		int u = read();
		int v = read();
		int cost = read();
		map[u][v] = std::max(map[u][v], cost);
		sl[u] = std::max(sl[u], map[u][v]);
	}
	for (int i = 1; i <= nl; i++)
	{
		bfs(i);
	}
	for (int i = 1; i <= n; i++)
	{
		ans += sl[i] + sr[i];
	}
	printf("%lld\n", ans);
	for (int i = 1; i <= n; i++)
	{
		pre[i] = 0;
	}
	for (int i = 1; i <= n; i++)
	{
		pre[match[i]] = i;
	}
	for (int i = 1; i <= nl; i++)
	{
		printf("%d ", map[i][pre[i]] ? pre[i] : 0);
	}
	puts("");
	return 0;
}
