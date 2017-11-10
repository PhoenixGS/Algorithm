#include <cstdio>

int a, x, b, y;

int extend_gcd(int a, int &x, int b, int &y)
{
	if (b == 0)
	{
		x = 1;
		y = 0;
		return a;
	}
	int d = extend_gcd(b, x, a % b, y);
	int tmp = x;
	x = y;
	y = tmp - a / b * y;
	return d;
}

int main()
{
	int a, b;
	scanf("%d%d", &a, &b);
	int d = extend_gcd(a, x, b, y);
	printf("%d %d %d\n", d, x, y);
	return 0;
}
