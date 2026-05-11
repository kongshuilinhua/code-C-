//
// Created by elysia on 2025/5/16.
// https://www.luogu.com.cn/problem/P2812
const int N = 1e4 + 10;
vvi g(N);
int dfn[N], low[N], tot;
int stk[N], in_stk[N], top;
int scc[N], scc_cnt;
void tarjan(int x)
{
    dfn[x] = low[x] = ++tot;
    stk[++top] = x;
    in_stk[x] = 1;
    for (auto y : g[x])
    {
        if (!dfn[y])
        {
            tarjan(y);
            low[x] = min(low[x], low[y]);
        }
        else if (in_stk[y])
        {
            low[x] = min(low[x], dfn[y]);
        }
    }
    if (dfn[x] == low[x])
    {
        scc_cnt++;
        int y;
        do
        {
            y = stk[top--];
            in_stk[y] = 0;
            scc[y] = scc_cnt;
        } while (y != x);
    }
}
void solve()
{
    int n, j;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        while (cin >> j)
        {
            if (j == 0)
                break;
            g[i].push_back(j);
        }
    }
    for (int i = 1; i <= n; i++)
        if (!dfn[i])
            tarjan(i);
    vi in(n + 1, 0), out(n + 1, 0);
    for (int i = 1; i <= n; i++)
    {
        for (auto j : g[i])
        {
            if (scc[i] != scc[j])
            {
                out[scc[i]]++;
                in[scc[j]]++;
            }
        }
    }
    int a = 0, b = 0;
    for (int i = 1; i <= scc_cnt; i++)
    {
        if (in[i] == 0)
            a++;
        if (out[i] == 0)
            b++;
    }
    print(a);
    if (scc_cnt == 1)
        print(0);
    else
        print(max(a, b));
}

