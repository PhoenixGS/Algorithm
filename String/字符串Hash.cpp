struct hash
{
    long long hash[2005];
    void make(int n, char *s)
    {
        hash[0] = 0;
        for (int i = 1; i <= n; i++)
        {
            hash[i] = (hash[i - 1] * 31 + s[i] - 'a') % M;
        }
    }
    long long cut(int l, int r)
    {
        return (hash[r] - hash[l - 1] * mi[r - l + 1] % M + M) % M;
    }
};

