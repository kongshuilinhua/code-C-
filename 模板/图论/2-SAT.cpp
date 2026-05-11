//
// Created by elysia on 2025/5/16.
// https://www.luogu.com.cn/problem/P4782
// https://codeforces.com/gym/104095/problem/F
const int N = 2e6 + 10;
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
    int n, m;
    cin >> n >> m;
    while (m--)
    {
        int i, a, j, b;
        cin >> i >> a >> j >> b;
        g[i + !a * n].push_back(j + b * n); // a真b假
        g[j + !b * n].push_back(i + a * n); // b假a真
    }
    for (int i = 1; i <= 2 * n; i++)
        if (!dfn[i])
            tarjan(i);
    for (int i = 1; i <= n; i++)
        if (scc[i] == scc[i + n])
            return print("IMPOSSIBLE");
    print("POSSIBLE");
    for (int i = 1; i <= n; i++)
        cout << (scc[i] > scc[i + n]) << " \n"[i == n];
}

// 记编号为i的点最终的点权为wi，只要所有边 u,v的中最大值尽可能小即可。或者说，最小化有边相连的景观值差距的最大值。不选是ai,选是bi
void solve()
{
    int n, m;
    cin >> n >> m;
    vi a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        cin >> b[i];
    vpii edges;
    while (m--)
    {
        int u, v;
        cin >> u >> v;
        edges.push_back({u, v});
    }
    auto check = [&](int mid) -> bool
    {
        for (int i = 1; i <= 2 * n; i++)
        {
            dfn[i] = low[i] = stk[i] = in_stk[i] = scc[i] = 0;
            g[i].clear();
        }
        tot = top = scc_cnt = 0;
        for (auto [u, v] : edges)
        {
            // 0 1  i  i + n
            // 枚举全部选择方案，选了之和>mid说明选则a就不能选择b
            if (abs(a[u] - a[v]) > mid)
            {
                g[u].push_back(v + n);
                g[v].push_back(u + n);
            }
            if (abs(a[u] - b[v]) > mid)
            {
                g[u].push_back(v);
                g[v + n].push_back(u + n);
            }
            if (abs(b[u] - a[v]) > mid)
            {
                g[u + n].push_back(v + n);
                g[v].push_back(u);
            }
            if (abs(b[u] - b[v]) > mid)
            {
                g[u + n].push_back(v);
                g[v + n].push_back(u);
            }
        }
        for (int i = 1; i <= 2 * n; i++)
            if (!dfn[i])
                tarjan(i);
        for (int i = 1; i <= n; i++)
            if (scc[i] == scc[i + n])
                return false;
        return true;
    };
    int l = 0, r = 1e9;
    while (l <= r)
    {
        int mid = (l + r) / 2;
        if (check(mid))
            r = mid - 1;
        else
            l = mid + 1;
    }
    print(l);
}
