#include <cstdio>

int gcd(int x, int y)
{
	return y == 0 ? x : gcd(y, x % y);
}

int main()
{
	int x, y;
	scanf("%d%d", &x, &y);
	printf("%d\n", gcd(x, y));
	return 0;
}
