#include <cstdio>
#include <cstring>
#include <queue>

int size;
int ch[10000][30];
int val[10000];
int f[10000];
int last[10000];
char st[10000];
char P[10000];
int n;

char id(char x)
{
	return x - 'a';
}

void insert(char* s, int v)
{
	int u = 0;
	int n = strlen(s + 1);
	for (int i = 1; i <= n; i++)
	{
		int c = id(s[i]);
		if (! ch[u][c])
		{
			size++;
			memset(ch[size], 0, sizeof(ch[size]));
			val[size] = 0;
			ch[u][c] = size;
		}
		u = ch[u][c];
	}
	val[u] = v;
}

void print(int i, int j)
{
	if (j)
	{
		printf("%d %d\n", i, val[j]);
		print(i, last[j]);
	}
}

void find(char * T)
{
	int n = strlen(T + 1);
	int j = 0;
	for (int i = 1; i <= n; i++)
	{
		int c = id(T[i]);
		j = ch[j][c];
		if (val[j])
		{
			print(i, j);
		}
		else
		{
			if (last[j])
			{
				print(i, last[j]);
			}
		}
	}
}

void getFail()
{
	std::queue<int> que;
	f[0] = 0;
	for (int c = 0; c < 26; c++)
	{
		int u = ch[0][c];
		if (u)
		{
			f[u] = 0;
			que.push(u);
			last[u] = 0;
		}
	}
	while (! que.empty())
	{
		int r = que.front();
		que.pop();
		for (int c = 0; c < 26; c++)
		{
			int u = ch[r][c];
			if (! u)
			{
				ch[r][c] = ch[f[r]][c];
				continue;
			}
			que.push(u);
			int v = f[r];
			while (v && ! ch[v][c])
			{
				v = f[v];
			}
			f[u] = ch[v][c];
			last[u] = val[f[u]] ? f[u] : last[f[u]];
		}
	}
}

int main()
{
	size = 0;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%s", st + 1);
		insert(st, i);
	}
	getFail();
	scanf("%s", P + 1);
	find(P);
	return 0;
}
