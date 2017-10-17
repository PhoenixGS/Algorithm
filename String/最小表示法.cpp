#include <cstdio>
#include <string>
#include <iostream>

std::string st;

int query(std::string st)
{
	int i = 0, j = 1;
	int n = st.length();
	st = st + st;
	while (j < n)
	{
		int k = 0;
		while (j + k < 2 * n && st[i + k] == st[j + k])
		{
			k++;
		}
		if (j + k == 2 * n)
		{
			break;
		}
		if (st[i + k] > st[j + k])
		{
			i = std::max(j, i + k + 1);
			j = i + 1;
		}
		else
		{
			j = j + k + 1;
		}
	}
	return i;
}

int main()
{
	std::cin >> st;
	int n = st.length();
	int t = query(st);
	st = st + st;
	for (int i = t; i <= t + n - 1; i++)
	{
		printf("%c", st[i]);
	}
	printf("\n");
	return 0;
}
