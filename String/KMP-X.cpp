#include <cstdio>
#include <cstring>

char st[10000];
char p[10000];
int f[10000];

void getFail(char* P, int* f)
{
	int m = strlen(P + 1);
	f[1] = 0;
	int k = 0;
	for (int q = 2; q <= m; q++)
	{
		while (k > 0 && P[k + 1] != P[q])
		{
			k = f[k];
		}
		if (P[k + 1] == P[q])
		{
			k++;
		}
		f[q] = k;
	}
}

void find(char* T, char* P, int* f)
{
	int n = strlen(T + 1);
	int m = strlen(P + 1);
	getFail(P, f);
	int q = 0; //已匹配的位数
	for (int i = 1; i <= n; i++)
	{
		while (q > 0 && P[q + 1] != T[i])
		{
			q = f[q];
		}
		if (P[q + 1] == T[i])
		{
			q = q + 1;
		}
		if (q == m)
		{
			printf("%d\n", i - m + 1);
			q = f[q];
		}
	}
}

int main()
{
	scanf("%s", st + 1);
	scanf("%s", p + 1);
	find(st, p, f);
	return 0;
}
