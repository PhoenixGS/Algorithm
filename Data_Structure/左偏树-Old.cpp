int merge(int x, int y)
{
	if (x == -1)
	{
		return y;
	}
	if (y == -1)
	{
		return x;
	}
	if (key[x] > key[y])
	{
		std::swap(x, y);
	}
	right[x] = merge(right[x], y);
	if (dis[left[x]] < dis[right[x]])
	{
		std::swap(left[x], right[x]);
	}
	if (right[x] == -1)
	{
		dis[x] = 0;
	}
	else
	{
		dis[x] = dis[right[x]] + 1;
	}
	return x;
}

int del(int root)
{
	int l = left[root];
	int r = right[root];
	dis[root] = 0;
	left[root] = right[root] = -1;
	return merge(l, r);
}
