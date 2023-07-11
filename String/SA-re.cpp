void rsort()
{
	for (int i = 0; i <= m; i++)
	{
		cnt[i] = 0;
	}
	for (int i = 1; i <= n; i++)
	{
		cnt[rk[tp[i]]]++;
	}
	for (int i = 1; i <= m; i++)
	{
		cnt[i] += cnt[i - 1];
	}
	for (int i = n; i >= 1; i--)
	{
		sa[cnt[rk[tp[i]]]--] = tp[i];
	}
}

void ssort()
{
	m = 127;
	for (int i = 1; i <= n; i++)
	{
		rk[i] = s[i];
		tp[i] = i;
	}
	rsort();
	for (int w = 1, p = 0; w <= n && p < n; w <<= 1, m = p)
	{
		p = 0;
		for (int i = n - w + 1; i <= n; i++)
		{
			p++;
			tp[p] = i;
		}
		for (int i = 1; i <= n; i++)
		{
			if (sa[i] > w)
			{
				p++;
				tp[p] = sa[i] - w;
			}
		}
		rsort();
		std::swap(rk, tp);
		rk[sa[1]] = p = 1;
		for (int i = 2; i <= n; i++)
		{
			if (tp[sa[i - 1]] == tp[sa[i]] && tp[std::min(n, sa[i - 1] + w)] == tp[std::min(n, sa[i] + w)])
			{
				rk[sa[i]] = p;
			}
			else
			{
				p++;
				rk[sa[i]] = p;
			}
		}
	}
}
