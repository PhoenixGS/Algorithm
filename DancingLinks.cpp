#include <cstdio>

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

int h[2000];
int s[2000];
int q[2000];
int up[2000000];
int down[2000000];
int left[2000000];
int right[2000000];
int C[2000000];
int X[2000000];
int n, m, size;

void del(int c)
{
	left[right[c]] = left[c];
	right[left[c]] = right[c];
	for (int i = down[c]; i != c; i = down[i])
	{
		for (int j = right[i]; j != i; j = right[j])
		{
			up[down[j]] = up[j];
			down[up[j]] = down[j];
			s[C[j]]--;
		}
	}
}

void add(int c)
{
	for (int i = up[c]; i != c; i = up[i])
	{
		for (int j = left[i]; j != i; j = left[j])
		{
			down[up[j]] = j;
			up[down[j]] = j;
			s[C[j]]++;
		}
	}
	right[left[c]] = c;
	left[right[c]] = c;
}

void link(int r, int c)
{
	size++;
	X[size] = r;
	C[size] = c;
	s[c]++;
	down[size] = down[c];
	up[size] = c;
	up[down[size]] = size;
	down[up[size]] = size;
	if (h[r] == -1)
	{
		h[r] = left[size] = right[size] = size;
	}
	else
	{
		right[size] = right[h[r]];
		left[size] = h[r];
		left[right[size]] = size;
		right[left[size]] = size;
	}
}

bool dance(int k)
{
	if (right[0] == 0)
	{
		printf("%d", k);
		for (int i = 1; i <= k; i++)
		{
			printf(" %d", X[q[i]]);
		}
		puts("");
		return 1;
	}
	int mn = INF;
	int c;
	for (int i = right[0]; i; i = right[i])
	{
		if (s[i] < mn)
		{
			mn = s[i];
			c = i;
		}
	}
	del(c);
	for (int i = down[c]; i != c; i = down[i])
	{
		q[k + 1] = i;
		for (int j = right[i]; j != i; j = right[j])
		{
			del(C[j]);
		}
		if (dance(k + 1))
		{
			return 1;
		}
		for (int j = left[i]; j != i; j = left[j])
		{
			add(C[j]);
		}
	}
	add(c);
	return 0;
}

int main()
{
	while (scanf("%d%d", &n, &m) == 2)
	{
		for (int i = 0; i < m; i++)
		{
			right[i] = i + 1;
		}
		right[m] = 0;
		for (int i = 1; i <= m; i++)
		{
			left[i] = i - 1;
		}
		left[0] = m;
		for (int i = 0; i <= m; i++)
		{
			down[i] = up[i] = i;
			s[i] = 0;
		}
		right[m] = 0;
		size = m;
		for (int i = 1; i <= n; i++)
		{
			h[i] = -1;
			int cnt = read();
			while (cnt--)
			{
				int tmp = read();
				link(i, tmp);
			}
		}
		if (! dance(0))
		{
			puts("NO");
		}
	}
	return 0;
}
