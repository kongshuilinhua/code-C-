// https://codeforces.com/gym/104081/problem/L
// https://codeforces.com/contest/600/problem/E
// 以 x为根的子树内，与 x 距离不超过 k 的点中，一共出现了多少种不同的颜色
void solve()
{
    int n, m;
    cin >> n >> m;
    vi a(n);
    for (auto &x : a)
        cin >> x;
    vvi g(n);
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vi res(n, 0), dep(n, 0);
    vector<unordered_map<int, int>> mp(n);
    vvi pos(n);
    auto dfs = [&](auto &&dfs, int x, int fa) -> void
    {
        pos[dep[x]].push_back(x);
        mp[x][a[x]]++;
        for (auto y : g[x])
        {
            if (y == fa)
                continue;
            dep[y] = dep[x] + 1;
            dfs(dfs, y, x);
            if (mp[y].size() > mp[x].size())
                swap(mp[y], mp[x]);
            for (auto [k, v] : mp[y])
                mp[x][k] += v;
            if (dep[x] + m + 1 < n)
            {
                for (auto i : pos[dep[x] + m + 1])
                {
                    if (--mp[x][a[i]] == 0)
                        mp[x].erase(a[i]);
                }
                pos[dep[x] + m + 1].clear();
            }
        }

        res[x] = mp[x].size();
    };
    dfs(dfs, 0, -1);

    int q;
    cin >> q;
    while (q--)
    {
        int x;
        cin >> x;
        print(res[x - 1]);
    }
}

// 如果一种颜色在以 x 为根的子树内出现次数最多，称其在以 x 为根的子树中占主导地位。显然，同一子树中可能有多种颜色占主导地位。
// 你的任务是对于每一个 i∈[1,n]，求出以 i 为根的子树中，占主导地位的颜色的编号和。
void solve()
{
    int n;
    cin >> n;
    vi col(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> col[i];

    vvi g(n + 1);
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vi cnt(n + 1, 0);
    HLD h(g);
    vi res(n + 1);
    int sum = 0, mx = 0;
    function<void(int, int, int, int)> add = [&](int x, int fa, int val, int p)
    {
        cnt[col[x]] += val;
        if (cnt[col[x]] > mx)
        {
            mx = cnt[col[x]];
            sum = col[x];
        }
        else if (cnt[col[x]] == mx)
        {
            sum += col[x];
        }
        for (auto y : g[x])
        {
            if (y == fa || y == p)
                continue;
            add(y, x, val, p);
        }
    };
    function<void(int, int, int)> dfs = [&](int x, int fa, int op)
    {
        for (auto y : g[x])
        {
            if (y == fa || y == h.son[x])
                continue;
            dfs(y, x, 0);
        }
        if (h.son[x])
            dfs(h.son[x], x, 1);
        add(x, fa, 1, h.son[x]);
        res[x] = sum;
        if (op == 0)
        {
            add(x, fa, -1, 0);
            sum = mx = 0;
        }
    };
    dfs(1, 0, 0);
    res.erase(res.begin());
    print(res);
}
