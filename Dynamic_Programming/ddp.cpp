//Luogu 4751
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

struct matrix
{
	int x[2][2];

	inline int * operator [] (int pos)
	{
		return x[pos];
	}
};

const int INF = 1000000000;
const int _n = 1000000 + 10;
int n, m;
int x[_n];
int edgenum;
int vet[2 * _n], nextx[2 * _n], head[_n];
int f[_n][2], g[_n][2];
int vis[_n];
int size[_n], son[_n], lsize[_n];
int ch[_n][2], fa[_n];
matrix mat[_n], mul[_n];
int last;
int z[_n];
int root;
int lastans;

matrix operator * (matrix x, matrix y)
{
	static matrix z;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			z[i][j] = -INF;
		}
	}
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			for (int k = 0; k < 2; k++)
			{
				z[i][j] = std::max(z[i][j], x[i][k] + y[k][j]);
			}
		}
	}
	return z;
}

void add(int u, int v)
{
	edgenum++;
	vet[edgenum] = v;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

void dfs(int u, int father)
{
	size[u] = 1;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father)
		{
			dfs(v, u);
			size[u] += size[v];
			if (size[v] > size[son[u]])
			{
				son[u] = v;
			}
		}
	}
}

void dfs2(int u, int father)
{
	lsize[u] = size[u] - size[son[u]];
	f[u][0] = 0;
	f[u][1] = x[u];
	g[u][0] = 0;
	g[u][1] = x[u];
	if (son[u])
	{
		dfs2(son[u], u);
		f[u][0] = f[u][0] + std::max(f[son[u]][0], f[son[u]][1]);
		f[u][1] = f[u][1] + f[son[u]][0];
	}
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father && v != son[u])
		{
			dfs2(v, u);
			f[u][0] = f[u][0] + std::max(f[v][0], f[v][1]);
			f[u][1] = f[u][1] + f[v][0];
			g[u][0] = g[u][0] + std::max(f[v][0], f[v][1]);
			g[u][1] = g[u][1] + f[v][0];
		}
	}
	mat[u][0][0] = g[u][0];
	mat[u][0][1] = g[u][0];
	mat[u][1][0] = g[u][1];
	mat[u][1][1] = -INF;
}

void pushup(int k)
{
	mul[k] = mat[k];
	if (ch[k][0])
	{
		mul[k] = mul[ch[k][0]] * mul[k];
	}
	if (ch[k][1])
	{
		mul[k] = mul[k] * mul[ch[k][1]];
	}
}

int sbuild(int l, int r)
{
	if (l > r)
	{
		return 0;
	}
	int tot = 0;
	int sum = 0;
	for (int i = l; i <= r; i++)
	{
		tot += lsize[z[i]];
	}
	for (int i = l; i <= r; i++)
	{
		sum += lsize[z[i]];
		if (2 * sum >= tot)
		{
			ch[z[i]][0] = sbuild(l, i - 1);
			ch[z[i]][1] = sbuild(i + 1, r);
			fa[ch[z[i]][0]] = z[i];
			fa[ch[z[i]][1]] = z[i];
			pushup(z[i]);
			return z[i];
		}
	}
}

int build(int root)
{
	for (int u = root; u; u = son[u])
	{
		vis[u] = 1;
	}
	for (int u = root; u; u = son[u])
	{
		for (int i = head[u]; i; i = nextx[i])
		{
			int v = vet[i];
			if (! vis[v])
			{
				int vroot = build(v);
				fa[vroot] = u;
			}
		}
	}
	last = 0;
	for (int u = root; u; u = son[u])
	{
		last++;
		z[last] = u;
	}
	return sbuild(1, last);
}

void change(int u, int newvalue)
{
	g[u][1] -= x[u];
	x[u] = newvalue;
	g[u][1] += x[u];
	mat[u][0][0] = g[u][0];
	mat[u][0][1] = g[u][0];
	mat[u][1][0] = g[u][1];
	mat[u][1][1] = -INF;
	for (int pos = u; pos; pos = fa[pos])
	{
		if (ch[fa[pos]][0] != pos && ch[fa[pos]][1] != pos)
		{
			g[fa[pos]][0] -= std::max(mul[pos][0][0], mul[pos][1][0]);
			g[fa[pos]][1] -= mul[pos][0][0];
			pushup(pos);
			g[fa[pos]][0] += std::max(mul[pos][0][0], mul[pos][1][0]);
			g[fa[pos]][1] += mul[pos][0][0];
			mat[fa[pos]][0][0] = g[fa[pos]][0];
			mat[fa[pos]][0][1] = g[fa[pos]][0];
			mat[fa[pos]][1][0] = g[fa[pos]][1];
			mat[fa[pos]][1][1] = -INF;
		}
		else
		{
			pushup(pos);
		}
	}
}

int main()
{
	scanf("%d%d",  &n, &m);
	for (int i = 1; i <= n; i++)
	{
		x[i] = read();
	}
	for (int i = 1; i < n; i++)
	{
		int u = read();
		int v = read();
		add(u, v);
		add(v, u);
	}
	dfs(1, 0);
	dfs2(1, 0);
	root = build(1);
	lastans = 0;
	while (m--)
	{
		int pos = read();
		int newvalue = read();
		pos = pos ^ lastans;
		change(pos, newvalue);
		lastans = std::max(mul[root][0][0], mul[root][1][0]);
		printf("%d\n", lastans);
	}
	return 0;
}

