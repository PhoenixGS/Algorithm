#include <cstdio>
#include <algorithm>

int n;
int x[1000];

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &x[i]);
	}
	for (int i = 1; i <= n; i++)
	{
		while (1 <= x[i] && x[i] <= n && x[i] != i)
		{
			if (x[x[i]] == x[i])
			{
				continue;
			}
			std::swap(x[x[i]], x[i]);
		}
	}
	for (int i = 1; i <= n; i++)
	{
		if (x[i] != i)
		{
			printf("%d\n", i);
			return 0;
		}
	}
	printf("%d\n", n + 1);
	return 0;
}
