#include <cstdio>
#include <algorithm>

int n;
int x[10000];

int maxbit(int *x, int n, int bit)
{
	int maxx = x[0];
	for (int i = 1; i < n; i++)
	{
		maxx = std::max(maxx, x[i]);
	}
	int d = 1;
	while (maxx >= bit)
	{
		maxx /= bit;
		d++;
	}
	return d;
}

void radixsort(int *x, int n)
{
	int bit = 10;
	int d = maxbit(x, n, bit);
	int *tmp = new int[n];
	int *count = new int[bit];
	int radix = 1;
	for (int i = 1; i <= d; i++)
	{
		for (int j = 0; j < bit; j++)
		{
			count[j] = 0;
		}
		for (int j = 0; j < n; j++)
		{
			int k = x[j] / radix % bit;
			count[k]++;
		}
		for (int j = 1; j < bit; j++)
		{
			count[j] = count[j] + count[j - 1];
		}
		for (int j = n - 1; j >= 0; j--)
		{
			int k = x[j] / radix % bit;
			tmp[count[k] - 1] = x[j];
			count[k]--;
		}
		for (int j = 0; j < n; j++)
		{
			x[j] = tmp[j];
		}
		radix = radix * bit;
	}
	delete []tmp;
	delete []count;
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &x[i]);
	}
	radixsort(x, n);
	for (int i = 0; i < n; i++)
	{
		printf("%d\n", x[i]);
	}
	return 0;
}
