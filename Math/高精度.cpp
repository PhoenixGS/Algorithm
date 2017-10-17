#include <cstdio>
#include <cstring>
#include <algorithm>

char s1[10000];
char s2[10000];

const int mi[4] = {1, 10, 100, 1000};
const int maxlen = 10000;
const int M = 10000;

struct BigNumber
{
	int v[maxlen];
	int length;

	BigNumber ()
	{
		length = 1;
		memset(v, 0, sizeof(v));
	}

	BigNumber (char *st)
	{
		int len = strlen(st + 1);
		length = (len - 1) / 4 + 1;
		memset(v, 0, sizeof(v));
		for (int i = 1; i <= len; i++)
		{
			v[(len - i) / 4 + 1] += mi[(len - i) % 4] * (st[i] - '0');
		}
		while (length > 1 && v[length] == 0)
		{
			length--;
		}
	}

	friend BigNumber operator + (const BigNumber &x, const BigNumber &y)
	{
		BigNumber z;
		z.length = std::max(x.length, y.length);
		int k = 0;
		for (int i = 1; i <= z.length; i++)
		{
			k = k + x.v[i] + y.v[i];
			z.v[i] = k % M;
			k /= M;
		}
		while (k != 0)
		{
			z.length++;
			z.v[z.length] = k % M;
			k /= M;
		}
		return z;
	}

	void print()
	{
		for (int i = length; i >= 1; i--)
		{
			printf("%d", v[i]);
		}
	}
};

int main()
{
	scanf("%s", s1 + 1);
	BigNumber x(s1);
	scanf("%s", s2 + 1);
	BigNumber y(s2);
	BigNumber z = x + y;
	x.print();
	printf("\n");
	y.print();
	printf("\n");
	z.print();
	printf("\n");
	return 0;
}
