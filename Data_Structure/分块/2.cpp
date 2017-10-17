#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>

long long read()
{
	char last = '+', ch = getchar();
	while (ch < '0' || ch > '9') last = ch, ch = getchar();
	long long tmp = 0;
	while (ch >= '0' && ch <= '9') tmp = tmp * 10 + ch - 48, ch = getchar();
	if (last == '-') tmp = -tmp;
	return tmp;
}

int n, m;
int x[10000];
std::vector<int> vec[100];
int knumber;
int knum[10000];
int tag[100];

void reset(int kk)
{
	vec[kk].clear();
	for (int i = (kk - 1) * knumber + 1; i <= std::min(kk * knumber, n); i++)
	{
		vec[kk].push_back(x[i]);
	}
	std::sort(vec[kk].begin(), vec[kk].end());
}

void update(int l, int r, int delta)
{
	if (knum[l] == knum[r])
	{
		for (int i = l; i <= r; i++)
		{
			x[i] += delta;
		}
		reset(knum[l]);
		return;
	}
	for (int i = l; i <= knum[l] * knumber; i++)
	{
		x[i] += delta;
	}
	reset(knum[l]);
	for (int i = (knum[r] - 1) * knumber + 1; i <= r; i++)
	{
		x[i] += delta;
	}
	reset(knum[r]);
	for (int i = knum[l] + 1; i <= knum[r] - 1; i++)
	{
		tag[i] += delta;
	}
}

int query(int l, int r, int key)
{
	int ans = 0;
	if (knum[l] == knum[r])
	{
		for (int i = l; i <= r; i++)
		{
			if (x[i] < key)
			{
				ans++;
			}
		}
		return ans;
	}
	for (int i = l; i <= knum[l] * knumber; i++)
	{
		if (x[i] < key)
		{
			ans++;
		}
	}
	for (int i = (knum[r] - 1) * knumber + 1; i <= r; i++)
	{
		if (x[i] < key)
		{
			ans++;
		}
	}
	for (int i = knum[l] + 1; i <= knum[r] - 1; i++)
	{
		ans += std::lower_bound(vec[i].begin(), vec[i].end(), key - tag[i]) - vec[i].begin();
	}
	return ans;
}

int main()
{
	n = read();
	for (int i = 1; i <= n; i++)
	{
		x[i] = read();
	}
	knumber = sqrt(n);
	for (int i = 1; i <= n; i++)
	{
		knum[i] = (i - 1) / knumber + 1;
		vec[knum[i]].push_back(x[i]);
	}
	for (int i = 1; i <= knum[n]; i++)
	{
		std::sort(vec[i].begin(), vec[i].end());
	}
	m = read();
	for (int i = 1; i <= m; i++)
	{
		int cas = read();
		if (cas == 0)
		{
			int l, r, delta;
			l = read();
			r = read();
			delta = read();
			update(l, r, delta);
		}
		else
		{
			int l, r, x;
			l = read();
			r = read();
			x = read();
			printf("%d\n", query(l, r, x));
		}
	}
	return 0;
}
