#include <cstdio>
#include <algorithm>

const int M = 998244353, G = 3;
const int _n = 64000 + 10;
int n, k;
int f[4 * _n], a[4 * _n];
int x[4 * _n], y[4 * _n], q[4 * _n], r[4 * _n];
int rev[4 * _n];
int xx[4 * _n], yy[4 * _n];
bool F = false;

int pow_mod(int x, int p, int M)
{
	p = (p % (M - 1) + M - 1) % (M - 1);
	int ans = 1;
	int tmp = x;
	while (p)
	{
		if (p & 1)
		{
			ans = (long long)ans * tmp % M;
		}
		tmp = (long long)tmp * tmp % M;
		p >>= 1;
	}
	return ans;
}

void getrev(int bit)
{
	rev[0] = 0;
	for (int i = 1; i < (1 << bit); i++)
	{
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
	}
}

void NTT(int *x, int n, int cas)
{
	for (int i = 0; i < n; i++)
	{
		if (i < rev[i])
		{
			std::swap(x[i], x[rev[i]]);
		}
	}
	for (int i = 1; i < n; i <<= 1)
	{
		int wn = pow_mod(G, cas * (M - 1) / (i << 1), M);
		for (int j = 0; j < n; j += (i << 1))
		{
			for (int k = 0, w = 1; k < i; k++, w = (long long)w * wn % M)
			{
				int xx = x[j + k];
				int yy = (long long)w * x[j + k + i] % M;
				x[j + k] = xx + yy;
                if (x[j + k] >= M)
                {
                    x[j + k] -= M;
                }
                if (x[j + k] < 0)
                {
                    x[j + k] += M;
                }
				x[j + k + i] = xx - yy;
                if (x[j + k + i] >= M)
                {
                    x[j + k + i] -= M;
                }
                if (x[j + k + i] < 0)
                {
                    x[j + k + i] += M;
                }
			}
		}
	}
	if (cas == -1)
	{
		int invn = pow_mod(n, M - 2, M);
		for (int i = 0; i < n; i++)
		{
			x[i] = (long long)x[i] * invn % M;
		}
	}
}

void poly_inv(int n, int *x, int *y)
{
	if (n == 1)
	{
		y[0] = pow_mod(x[0], M - 2, M);
		return;
	}
	poly_inv((n + 1) / 2, x, y);
	int N = 1;
	int bit = 0;
	while (N < 2 * n)
	{
		N <<= 1;
		bit++;
	}
	for (int i = 0; i < N; i++)
	{
		xx[i] = yy[i] = 0;
	}
	for (int i = 0; i < n; i++)
	{
		xx[i] = x[i];
	}
	for (int i = 0; i < (n + 1) / 2; i++)
	{
		yy[i] = y[i];
	}
	getrev(bit);
	NTT(xx, N, 1);
	NTT(yy, N, 1);
	for (int i = 0; i < N; i++)
	{
		xx[i] = (long long)xx[i] * yy[i] % M * yy[i] % M;
	}
	NTT(xx, N, -1);
	for (int i = 0; i < n; i++)
	{
		y[i] = ((long long)2 * y[i] % M - xx[i]) % M;
	}
}

void poly_div(int n, int m, int *x, int *y, int *q, int *r)
{
    static int z[4 * _n];
    std::reverse(x, x + n);
    std::reverse(y, y + m);
    if (F == false)
    {
        F = true;
        poly_inv(n - m + 1, y, z);
    }
    int N = 1;
    int bit = 0;
    while (N <= n)
    {
        N <<= 1;
        bit++;
    }
    for (int i = 0; i < N; i++)
    {
        xx[i] = yy[i] = 0;
    }
    for (int i = 0; i < n - m + 1; i++)
    {
        xx[i] = x[i];
    }
    for (int i = 0; i < n - m + 1; i++)
    {
        yy[i] = z[i];
    }
    getrev(bit);
    NTT(xx, N, 1);
    NTT(yy, N, 1);
    for (int i = 0; i < N; i++)
    {
        xx[i] = (long long)xx[i] * yy[i] % M;
    }
    NTT(xx, N, -1);
    for (int i = 0; i < n - m + 1; i++)
    {
        q[i] = xx[i];
    }
    std::reverse(x, x + n);
    std::reverse(y, y + m);
    std::reverse(q, q + n - m + 1);
    for (int i = 0; i < N; i++)
    {
        xx[i] = yy[i] = 0;
    }
    for (int i = 0; i < m; i++)
    {
        xx[i] = y[i];
    }
    for (int i = 0; i < n - m + 1; i++)
    {
        yy[i] = q[i];
    }
    NTT(xx, N, 1);
    NTT(yy, N, 1);
    for (int i = 0; i < N; i++)
    {
        xx[i] = (long long)xx[i] * yy[i] % M;
    }
    NTT(xx, N, -1);
    for (int i = 0; i < m - 1; i++)
    {
        r[i] = ((x[i] - xx[i]) % M + M) % M;
    }
}

int rec(int n, int *f, int *a, int p)
{
    static int tmp[4 * _n], ans[4 * _n], q[4 * _n], r[4 * _n];
    ans[0] = 1;
    tmp[1] = 1;
    int N = 1;
    int bit = 0;
    while (N <= 2 * n)
    {
        N <<= 1;
        bit++;
    }
    while (p)
    {
        if (p & 1)
        {
            for (int i = 0; i < N; i++)
            {
                xx[i] = yy[i] = 0;
            }
            for (int i = 0; i < n - 1; i++)
            {
                xx[i] = ans[i];
                yy[i] = tmp[i];
            }
            getrev(bit);
            NTT(xx, N, 1);
            NTT(yy, N, 1);
            for (int i = 0; i < N; i++)
            {
                xx[i] = (long long)xx[i] * yy[i] % M;
            }
            NTT(xx, N, -1);
            for (int i = 0; i < 2 * n; i++)
            {
                ans[i] = xx[i];
            }
            poly_div(2 * n, n, ans, f, q, r);
            for (int i = 0; i < n - 1; i++)
            {
                ans[i] = r[i];
            }
        }
        for (int i = 0; i < N; i++)
        {
            xx[i] = 0;
        }
        for (int i = 0; i < n - 1; i++)
        {
            xx[i] = tmp[i];
        }
        getrev(bit);
        NTT(xx, N, 1);
        for (int i = 0; i < N; i++)
        {
            xx[i] = (long long)xx[i] * xx[i] % M;
        }
        NTT(xx, N, -1);
        for (int i = 0; i < 2 * n; i++)
        {
            tmp[i] = xx[i];
        }
        poly_div(2 * n, n, tmp, f, q, r);
        for (int i = 0; i < n - 1; i++)
        {
            tmp[i] = r[i];
        }
        p >>= 1;
    }
    int anss = 0;
    for (int i = 0; i < n - 1; i++)
    {
        anss = (anss + (long long)ans[i] * a[i] % M) % M;
    }
    return (anss + M) % M;
}

int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 0; i < k; i++)
    {
        scanf("%d", &f[i]);
    }
    for (int i = 0; i < k; i++)
    {
        scanf("%d", &a[i]);
    }
    std::reverse(f, f + k);
    for (int i = 0; i < k; i++)
    {
        f[i] = -f[i];
    }
    k++;
    f[k - 1] = 1;
    printf("%d\n", rec(k, f, a, n));
    return 0;
}


