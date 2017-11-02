#include <cstdio>

int edgenum;
int vet[2000000];
int nextx[2000000];
int head[600000];
int quesnum;
int quesvet[2000000];
int quesnextx[2000000];
int queshead[600000];
int anc[600000];
int f[600000];
int rank[600000];
int ans[2000000];
int color[600000];
int n, m, root;

void add(int u, int v)
{
	edgenum++;
	vet[edgenum] = v;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

void quesadd(int u, int v)
{
	quesnum++;
	quesvet[quesnum] = v;
	quesnextx[quesnum] = queshead[u];
	queshead[u] = quesnum;
}

void makeset(int x)
{
	f[x] = x;
	rank[x] = 0;
}

int findfather(int x)
{
	return f[x] == x ? x : f[x] = findfather(f[x]);
}

void link(int x, int y)
{
	if (rank[x] > rank[y])
	{
		f[y] = x;
	}
	else
	{
		f[x] = y;
		if (rank[x] == rank[y])
		{
			rank[y]++;
		}
	}
}

void unionx(int x, int y)
{
	int xx = findfather(x);
	int yy = findfather(y);
	if (xx != yy)
	{
		link(xx, yy);
	}
}

void LCA(int u, int father)
{
	makeset(u);
	anc[findfather(u)] = u;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father)
		{
			LCA(v, u);
			unionx(u, v);
			anc[findfather(u)] = u;
		}
	}
	color[u] = 1;
	for (int i = queshead[u]; i; i = quesnextx[i])
	{
		int v = quesvet[i];
		if (color[v])
		{
			ans[i] = ans[i ^ 1] = anc[findfather(v)];
		}
	}
}

int main()
{
	edgenum = 0;
	quesnum = 1;
	scanf("%d%d%d", &n, &m, &root);
	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v);
		add(v, u);
	}
	for (int i = 1; i <= n; i++)
	{
		color[i] = 0;
	}
	for (int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		quesadd(u, v);
		quesadd(v, u);
	}
	LCA(root, -1);
	for (int i = 1; i <= m; i++)
	{
		printf("%d\n", ans[i * 2]);
	}
	return 0;
}
