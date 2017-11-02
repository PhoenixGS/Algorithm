#include <cstdio>
#include <algorithm>
#include <map>
#include <cmath>

long long c, a, b;
std::map<long long, long long> map;
long long m;

long long pow_mod(long long x, long long p, long long M)
{
	long long ans = 1;
	long long tmp = x % M;
	while (p)
	{
		if (p & 1)
		{
			ans = ans * tmp % M;
		}
		tmp = tmp * tmp % M;
		p >>= 1;
	}
	return ans;
}

int main()
{
	while (scanf("%lld%lld%lld", &c, &a, &b) == 3)
	{
		map.clear();
		if (a % c == 0)
		{
			printf("no solution\n");
			continue;
		}
		int flag = false;
		m = ceil(sqrt(c));
		long long ans;
		for (int i = 0; i <= m; i++)
		{
			if (i == 0)
			{
				ans = b % c;
				map[ans] = i;
				continue;
			}
			ans = (ans * a) % c;
			map[ans] = i;
		}
		long long t = pow_mod(a, m, c);
		ans = 1;
		for (int i = 1; i <= m; i++)
		{
			ans = (ans * t) % c;
			if (map[ans])
			{
				long long tmp = i * m - map[ans];
				printf("%lld\n", tmp);
				flag = true;
				break;
			}
		}
		if (! flag)
		{
			printf("no solution\n");
		}
	}
	return 0;
}
