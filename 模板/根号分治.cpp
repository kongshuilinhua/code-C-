// https://atcoder.jp/contests/abc359/tasks/abc359_g
// https://codeforces.com/problemset/problem/1921/F
// https://codeforces.com/problemset/problem/1207/F
// 树上颜色相同的点之间的距离之和  N为1e5
void solve()
{
    int n;
    cin >> n;

    vvi col(n + 1);
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vi a(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        col[a[i]].push_back(i);
    }
    ll res = 0;

    dfs(1, 0, 0);
    for (int i = 1; i <= __lg(n); i++)
        for (int j = 1; j + (1 << i) - 1 <= n; j++)
            mi[i][j] = get(mi[i - 1][j], mi[i - 1][j + (1 << i - 1)]);
    int B = 550;

    for (int k = 1; k <= n; k++)
    {
        int m = col[k].size();
        if (m < B)
        {
            for (int i = 0; i < m; i++)
            {
                for (int j = i + 1; j < m; j++)
                {
                    res += d[col[k][i]] + d[col[k][j]] - 2 * d[lca(col[k][i], col[k][j])];
                }
            }
        }
        else
        {
            vi sz(n + 1, 0);
            auto dfs1 = [&](auto &&dfs1, int x, int fa) -> void
            {
                if (a[x] == k)
                    sz[x] = 1;
                for (auto y : g[x])
                {
                    if (y == fa)
                        continue;
                    dfs1(dfs1, y, x);
                    sz[x] += sz[y];
                }
            };
            dfs1(dfs1, 1, 0);

            auto dfs2 = [&](auto &&dfs2, int x, int fa) -> void
            {
                if (sz[x] == 0)
                    return;
                for (auto y : g[x])
                {
                    if (y == fa)
                        continue;
                    res += 1LL * sz[y] * (sz[1] - sz[y]);
                    dfs2(dfs2, y, x);
                }
            };
            dfs2(dfs2, 1, 0);
        }
    }
    print(res);
}