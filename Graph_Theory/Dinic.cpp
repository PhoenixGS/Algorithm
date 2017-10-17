#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

int edgenum;
int vet[1000];
int cap[1000];
int flow[1000];
int nextx[1000];
int head[1000];
bool vis[1000];
int dis[1000];
queue<int> Q;
const int INF = 1000000000;
int n, m;

void add(int u, int v, int c)
{
	edgenum++;
	vet[edgenum] = v;
	cap[edgenum] = c;
	flow[edgenum] = 0;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
	edgenum++;
	vet[edgenum] = u;
	cap[edgenum] = 0;
	flow[edgenum] = 0;
	nextx[edgenum] = head[v];
	head[v] = edgenum;
}

int bfs(int s, int t)
{
	memset(vis, 0, sizeof(vis));
	Q.push(s);
	vis[s] = 1;
	dis[s] = 0;
	while (! Q.empty())
	{
		int u = Q.front();
		Q.pop();
		for (int i = head[u]; i; i = nextx[i])
		{
			int v = vet[i];
			if (! vis[v] && cap[i] > flow[i])
			{
				vis[v] = 1;
				dis[v] = dis[u] + 1;
				Q.push(v);
			}
		}
	}
	return vis[t];
}

int dfs(int u, int t, int maxf)
{
	if (u == t)
	{
		return maxf;
	}
	int ansflow = 0;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		int f;
		if (dis[u] + 1 == dis[v] && (f = dfs(v, t, min(maxf, cap[i] - flow[i]))) > 0)
		{
			flow[i] += f;
			flow[i ^ 1] -= f;
			ansflow += f;
			maxf -= f;
			if (maxf == 0)
			{
				break;
			}
		}
	}
	return ansflow;
}

int maxflow(int s, int t)
{
	int flow = 0;
	while (bfs(s, t))
	{
		flow += dfs(s, t, INF);
	}
	return flow;
}

int main()
{
	edgenum = 1;
	scanf("%d%d", &m, &n);
	for (int i = 1; i <= m; i++)
	{
		int u, v, c;
		scanf("%d%d%d", &u, &v, &c);
		add(u, v, c);
	}
	printf("%d\n", maxflow(1, n));
	return 0;
}
