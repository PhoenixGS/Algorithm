//C++
int main()
{
    scanf("%s", kst + 1);
    klen = strlen(kst + 1);
    len = 2 * klen + 1;
    st[1] = '#';
    for (int i = 1; i <= klen; i++)
    {
        st[2 * i] = kst[i];
        st[2 * i + 1] = '#';
    }
    st[len + 1] = '\0';
    maxright = 0;
    pos = 0;
    maxlen = 0;
    for (int i = 1; i <= len; i++)
    {
        if (i <= maxright)
        {
            RL[i] = min(RL[2 * pos - i], maxright - i);
        }
        else
        {
            RL[i] = 0;
        }
        while (i - RL[i] - 1 >= 1 && i + RL[i] + 1 <= len && st[i - RL[i] - 1] == st[i + RL[i] + 1])
        {
            RL[i]++;
        }
        if (i + RL[i] > maxright)
        {
            maxright = i + RL[i];
            pos = i;
        }
        maxlen = max(maxlen, RL[i]);
    }
    printf("%d\n", maxlen);
}
