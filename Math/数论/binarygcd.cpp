#include <cstdio>
#include <cmath>
#include <cstdlib>

int gcd(int x, int y)
{
	x = abs(x);
	y = abs(y);
	if (x < y)
	{
		return gcd(y, x);
	}
	if (y == 0)
	{
		return x;
	}
	if ((x & 1) == 0 && (y & 1) == 0)
	{
		return gcd(x >> 1, y >> 1) << 1;
	}
	if ((x & 1) == 1 && (y & 1) == 0)
	{
		return gcd(x, y >> 1);
	}
	if ((x & 1) == 0 && (y & 1) == 1)
	{
		return gcd(x >> 1, y);
	}
	return gcd((x - y) >> 1, y);
}

int main()
{
	int x, y;
	scanf("%d%d", &x, &y);
	printf("%d\n", gcd(x, y));
	return 0;
}
