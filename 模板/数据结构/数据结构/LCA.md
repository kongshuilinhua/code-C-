# 最近公共祖先  LCA
```c++
// 斜二进制LCA
vi fa(n + 1, 0), lb(n + 1, 0), d(n + 1, 0);
function<void(int)> dfs = [&](int x)
{
    int p = fa[x], q = lb[p], r = lb[q];
    d[x] = d[p] + 1;
    lb[x] = d[p] - d[q] != d[q] - d[r] ? p : r;
    for (int y : g[x])
        if (y != p)
            fa[y] = x, dfs(y);
};
function<int(int, int)> lca = [&](int u, int v)
{
    if (d[u] < d[v])
        swap(u, v);
    while (d[u] > d[v])
        if (d[lb[u]] < d[v])
            u = fa[u];
        else
            u = lb[u];
    while (u != v)
        if (lb[u] == lb[v])
            u = fa[u], v = fa[v];
        else
            u = lb[u], v = lb[v];
    return u;
};
dfs(1);

// dfs序求LCA  nlogn预处理 O1查询
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 5e5 + 5;
int n, m, R, dn, dfn[N], mi[19][N];
vector<int> e[N];
int get(int x, int y) { return dfn[x] < dfn[y] ? x : y; }
void dfs(int x, int fa)
{
    mi[0][dfn[x] = ++dn] = fa;
    for (int y : e[x])
        if (y != fa)
            dfs(y, x);
}
int lca(int u, int v)
{
    if (u == v)
        return u;
    if ((u = dfn[u]) > (v = dfn[v]))
        swap(u, v);
    int d = __lg(v - u++);
    return get(mi[d][u], mi[d][v - (1 << d) + 1]);
}

void solve()
{
    cin >> n >> m >> R;
    for (int i = 2, u, v; i <= n; i++)
    {
        cin >> u >> v;
        e[u].push_back(v), e[v].push_back(u);
    }
    dfs(R, 0);
    for (int i = 1; i <= __lg(n); i++)
        for (int j = 1; j + (1 << i) - 1 <= n; j++)
            mi[i][j] = get(mi[i - 1][j], mi[i - 1][j + (1 << i - 1)]);
}

```