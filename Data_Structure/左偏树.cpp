int merge(int x, int y)
{
	if (x == 0 || y == 0)
	{
		return x + y;
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
	dis[x] = dis[right[x]] + 1;
	return x;
}

int del(int x)
{
	int l = left[x];
	int r = right[x];
	dis[x] = 1;
	left[x] = right[root] = 0;
	return merge(l, r);
}
