#include <cstdio>
#include <cstring>

char s[2000000];
char t[2000000];
int n, m;
int f[2000000];

void getf()
{
	int now = 0;
	f[1] = 0;
	for (int i = 2; i <= m; i++)
	{
		while (now && t[i] != t[now + 1])
		{
			now = f[now];
		}
		if (t[i] == t[now + 1])
		{
			now++;
		}
		f[i] = now;
	}
}

void solve()
{
	int now = 0;
	for (int i = 1; i <= n; i++)
	{
		while (now && s[i] != t[now + 1])
		{
			now = f[now];
		}
		if (s[i] == t[now + 1])
		{
			now++;
			if (now == m)
			{
				printf("%d\n", i - now + 1);
				now = f[now];
			}
		}
	}
}

int main()
{
	scanf("%s", s + 1);
	scanf("%s", t + 1);
	n = strlen(s + 1);
	m = strlen(t + 1);
	getf();
	solve();
	return 0;
}
