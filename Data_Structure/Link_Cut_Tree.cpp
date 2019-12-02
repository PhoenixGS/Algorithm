//BZOJ 1036
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

const int _n = 30000 + 10;
int n, m;
int key[_n], sum[_n], maxx[_n], ch[_n][2], fa[_n], tag[_n];
int top;
int stack[_n];
char s[100];

bool isroot(int x)
{
	return ch[fa[x]][0] != x && ch[fa[x]][1] != x;
}

void pushup(int x)
{
	sum[x] = sum[ch[x][0]] + sum[ch[x][1]] + key[x];
	maxx[x] = std::max(std::max(maxx[ch[x][0]], maxx[ch[x][1]]), key[x]);
}

void pushdown(int x)
{
	if (tag[x])
	{
		std::swap(ch[x][0], ch[x][1]);
		tag[ch[x][0]] ^= 1;
		tag[ch[x][1]] ^= 1;
		tag[x] = 0;
	}
}

void rotate(int x)
{
	int y = fa[x];
	int z = fa[y];
	int w = ch[y][1] == x;
	if (! isroot(y))
	{
		ch[z][ch[z][1] == y] = x;
	}
	fa[x] = z;
	ch[y][w] = ch[x][w ^ 1];
	fa[ch[y][w]] = y;
	ch[x][w ^ 1] = y;
	fa[y] = x;
	pushup(y);
	pushup(x);
}

void splay(int x)
{
	top = 0;
	top++;
	stack[top] = x;
	for (int i = x; ! isroot(i); i = fa[i])
	{
		top++;
		stack[top] = fa[i];
	}
	while (top)
	{
		pushdown(stack[top]);
		top--;
	}
	while (! isroot(x))
	{
		int y = fa[x];
		int z = fa[y];
		if (! isroot(y))
		{
			if ((ch[z][0] == y) ^ (ch[y][0] == x))
			{
				rotate(x);
			}
			else
			{
				rotate(y);
			}
		}
		rotate(x);
	}
}

void access(int x)
{
	for (int i = x, t = 0; i; t = i, i = fa[i])
	{
		splay(i);
		ch[i][1] = t;
		pushup(i);
	}
}

void makeroot(int x)
{
	access(x);
	splay(x);
	tag[x] ^= 1;
}

void link(int x, int y)
{
	makeroot(x);
	fa[x] = y;
}

void split(int x, int y)
{
	makeroot(x);
	access(y);
	splay(x);
}

int main()
{
	maxx[0] = -1000000000;
	scanf("%d", &n);
	for (int i = 1; i < n; i++)
	{
		int u = read();
		int v = read();
		link(u, v);
	}
	for (int i = 1; i <= n; i++)
	{
		int x = read();
		splay(i);
		key[i] = x;
		pushup(i);
	}
	scanf("%d", &m);
	while (m--)
	{
		scanf("%s", s + 1);
		if (s[1] == 'C')
		{
			int pos = read();
			int newvalue = read();
			splay(pos);
			key[pos] = newvalue;
			pushup(pos);
		}
		if (s[2] == 'M')
		{
			int u = read();
			int v = read();
			split(u, v);
			printf("%d\n", maxx[u]);
		}
		if (s[2] == 'S')
		{
			int u = read();
			int v = read();
			split(u, v);
			printf("%d\n", sum[u]);
		}
	}
	return 0;
}
