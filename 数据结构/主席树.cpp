#include <cstdio>

int n, m;
int knum;
int lson[8000000];
int rson[8000000];
int sum[8000000];
int root[200000];
const int INF = 1000000000;

void build(int u, int &v, int l, int r, int x)
{
	knum++;
	v = knum;
	lson[v] = lson[u];
	rson[v] = rson[u];
	sum[v] = sum[u] + 1;
	if (l == r)
	{
		return;
	}
	int mid = (l + r) >> 1;
	if (x <= mid)
	{
		build(lson[u], lson[v], l, mid, x);
	}
	else
	{
		build(rson[u], rson[v], mid + 1, r, x);
	}
}

int query(int u, int v, int l, int r, int k)
{
	if (l == r)
	{
		return l;
	}
	int mid = (l + r) >> 1;
	int t = sum[lson[u]] - sum[lson[v]];
	if (k <= t)
	{
		return query(lson[u], lson[v], l, mid, k);
	}
	else
	{
		return query(rson[u], rson[v], mid + 1, r, k - t);
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	knum = 0;
	for (int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x);
		build(root[i - 1], root[i], -INF, INF, x);
	}
	while (m--)
	{
		int l, r, k;
		scanf("%d%d%d", &l, &r, &k);
		printf("%d\n", query(root[r], root[l - 1], -INF, INF, k));
	}
	return 0;
}
