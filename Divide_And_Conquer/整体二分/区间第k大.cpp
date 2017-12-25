//POJ 2104
#include <cstdio>

struct T
{
	int cas;
	int l, r, k;
	int x;
	int id;
};

const int INF = 1e9;
int n, m;
T ques[200000], ques1[200000], ques2[200000];
int bit[200000];
int last;
int ans[200000];

int lowbit(int x)
{
	return x & -x;
}

void add(int x, int delta)
{
	for (int i = x; i <= n; i += lowbit(i))
	{
		bit[i] += delta;
	}
}

int query(int x)
{
	int ans = 0;
	for (int i = x; i; i -= lowbit(i))
	{
		ans += bit[i];
	}
	return ans;
}

void solve(int quesl, int quesr, int l, int r)
{
	if (quesl > quesr)
	{
		return;
	}
	if (l == r)
	{
		for (int i = quesl; i <= quesr; i++)
		{
			if (ques[i].cas == 2)
			{
				ans[ques[i].id] = l;
			}
		}
		return;
	}
	int mid = l + r >> 1;
	int k1 = 0, k2 = 0;
	for (int i = quesl; i <= quesr; i++)
	{
		if (ques[i].cas == 1)
		{
			if (ques[i].x <= mid)
			{
				add(ques[i].id, 1);
				k1++;
				ques1[k1] = ques[i];
			}
			else
			{
				k2++;
				ques2[k2] = ques[i];
			}
		}
		else
		{
			int cnt = query(ques[i].r) - query(ques[i].l - 1);
			if (cnt >= ques[i].k)
			{
				k1++;
				ques1[k1] = ques[i];
			}
			else
			{
				ques[i].k -= cnt;
				k2++;
				ques2[k2] = ques[i];
			}
		}
	}
	for (int i = 1; i <= k1; i++)
	{
		if (ques1[i].cas == 1)
		{
			add(ques1[i].id, -1);
		}
	}
	for (int i = 1; i <= k1; i++)
	{
		ques[quesl + i - 1] = ques1[i];
	}
	for (int i = 1; i <= k2; i++)
	{
		ques[quesl + k1 + i - 1] = ques2[i];
	}
	solve(quesl, quesl + k1 - 1, l, mid);
	solve(quesl + k1, quesr, mid + 1, r);
}

int main()
{
	scanf("%d%d", &n, &m);
	last = 0;
	for (int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x);
		last++;
		ques[last].cas = 1;
		ques[last].x = x;
		ques[last].id = i;
	}
	for (int i = 1; i <= m; i++)
	{
		int l, r, k;
		scanf("%d%d%d", &l, &r, &k);
		last++;
		ques[last].cas = 2;
		ques[last].l = l;
		ques[last].r = r;
		ques[last].k = k;
		ques[last].id = i;
	}
	solve(1, last, -INF, INF);
	for (int i = 1; i <= m; i++)
	{
		printf("%d\n", ans[i]);
	}
	return 0;
}
