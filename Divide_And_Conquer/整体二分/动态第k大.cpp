//ZOJ 2112
#include <cstdio>

struct node
{
	int cas;
	int l, r, k;
	int x, delta;
	int id;
};

const int INF = 1000000000;
int T;
int n, m;
int last;
node ques[100000], ques1[100000], ques2[100000];
int bit[100000];
int cas[100000];
char st[100];
int x[100000];
int ans[100000];

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
				add(ques[i].id, ques[i].delta);
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
			if (ques[i].k <= cnt)
			{
				k1++;
				ques1[k1] = ques[i];
			}
			else
			{
				k2++;
				ques[i].k -= cnt;
				ques2[k2] = ques[i];
			}
		}
	}
	for (int i = 1; i <= k1; i++)
	{
		if (ques1[i].cas == 1)
		{
			add(ques1[i].id, -ques1[i].delta);
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
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d%d", &n, &m);
		last = 0;
		for (int i = 1; i <= n; i++)
		{
			scanf("%d", &x[i]);
			last++;
			ques[last].cas = 1;
			ques[last].x = x[i];
			ques[last].delta = 1;
			ques[last].id = i;
		}
		for (int i = 1; i <= m; i++)
		{
			scanf("%s", st + 1);
			if (st[1] == 'Q')
			{
				cas[i] = 2;
				int l, r, k;
				scanf("%d%d%d", &l, &r, &k);
				last++;
				ques[last].cas = 2;
				ques[last].l = l;
				ques[last].r = r;
				ques[last].k = k;
				ques[last].id = i;
			}
			else
			{
				cas[i] = 1;
				int pos, newvalue;
				scanf("%d%d", &pos, &newvalue);
				last++;
				ques[last].cas = 1;
				ques[last].x = x[pos];
				ques[last].delta = -1;
				ques[last].id = pos;
				x[pos] = newvalue;
				last++;
				ques[last].cas = 1;
				ques[last].x = x[pos];
				ques[last].delta = 1;
				ques[last].id = pos;
			}
		}
		solve(1, last, -INF, INF);
		for (int i = 1; i <= m; i++)
		{
			if (cas[i] == 2)
			{
				printf("%d\n", ans[i]);
			}
		}
	}
	return 0;
}
