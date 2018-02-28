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
	int l = 1;
	int r = n;
	while (l <= r)
	{
		if (x[l] == l)
		{
			l++;
		}
		else
		{
			if (x[l] < l || x[l] > r || x[x[l]] == x[l])
			{
				x[l] = x[r];
				r--;
			}
			else
			{
				std::swap(x[l], x[x[l]]);
			}
		}
	}
	printf("%d\n", l);
	return 0;
}
