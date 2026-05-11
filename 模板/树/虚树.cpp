// https://codeforces.com/problemset/problem/613/D
// https://www.luogu.com.cn/problem/P2495
// https://ac.nowcoder.com/acm/contest/115567/J
const int inf = 1e18;
// const int mod = 1e9 + 7;
struct HLD
{
    vi fa, dep, sz, son, id, top, last, rnk;
    // fa[u]: u的父节点
    // dep[u]: u的深度
    // son[u]: u的重儿子
    // sz[u]: 以u为根的子树的结点数
    // top[u]: u所在的重链的顶点编号
    // id[u] : u剖分后的新编号
    // rnk[u]: 分配后的新编号u对应的原编号
    // last[u]:记录每个重链的区间在 DFS 序中的最后一个编号。
    HLD(vvi &g, int root = 1)
    {
        int N = g.size();
        fa.resize(N, 0);
        dep.resize(N, 0);
        sz.resize(N, 0);
        son.resize(N, 0);
        function<void(int, int)> dfs = [&](int x, int father)
        {
            fa[x] = father;
            sz[x] = 1;
            dep[x] = dep[father] + 1;
            for (auto &v : g[x])
            {
                int y = v;
                if (y == father)
                    continue;
                dfs(y, x);
                sz[x] += sz[y];
                if (sz[son[x]] < sz[y])
                {
                    son[x] = y;
                }
            }
        };
        dfs(root, 0);

        id.resize(N, 0);
        top.resize(N, 0);
        last.resize(N, 0);
        rnk.resize(N, 0);
        int cnt = 0;
        function<void(int, int)> dfs2 = [&](int x, int tc)
        {
            top[x] = tc;
            id[x] = ++cnt;
            last[tc] = cnt;
            rnk[cnt] = x;
            if (son[x] == 0)
                return;
            dfs2(son[x], tc);
            for (auto &v : g[x])
            {
                int y = v;
                if (y != son[x] && y != fa[x])
                    dfs2(y, y);
            }
        };
        dfs2(root, root);
    }
    // 获取u-v最短路径之间的结点编号
    vector<pii> getpath(int u, int v)
    {
        vector<pii> res;
        while (top[u] != top[v])
        {
            if (dep[top[u]] < dep[top[v]])
                swap(u, v);
            res.push_back({id[top[u]], id[u]});
            u = fa[top[u]];
        }
        if (dep[u] < dep[v])
            swap(u, v);
        res.push_back({id[v], id[u]});
        return res;
    }
    // 获取u子树的所有结点编号
    vector<pii> getnodepath(int u)
    {
        vector<pii> res;
        res.push_back({id[u], id[u] + sz[u] - 1});
        return res;
    }

    int lca(int u, int v)
    {
        while (top[u] != top[v])
        {
            if (dep[top[u]] < dep[top[v]])
                swap(u, v);
            u = fa[top[u]];
        }
        return dep[u] < dep[v] ? u : v;
    }
};

void solve()
{
    int n;
    cin >> n;
    vvi g(n + 1);
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    HLD hld(g);
    int time = 0;
    vi dfn(n + 1);
    auto dfs = [&](auto &&dfs, int x, int fa) -> void
    {
        dfn[x] = time++;
        for (auto y : g[x])
        {
            if (y != fa)
            {
                dfs(dfs, y, x);
            }
        }
    };
    dfs(dfs, 1, 0);
    vvi G(n + 1);
    vi vis;
    auto add = [&](int x, int y)
    {
        G[x].push_back(y);
        G[y].push_back(x);
        vis.push_back(x);
        vis.push_back(y);
    };
    auto build_virtual_tree = [&](vi &b)
    {
        if (b.size() == 0)
            return;
        for (auto x : vis)
            G[x].clear();
        vis.clear();
        sort(all(b), [&](int x, int y)
        { return dfn[x] < dfn[y]; }); // 关键点按照dfs序排序
        vi st(2 * b.size() + 10);
        int top = 1;
        st[top] = 1; // 根节点入栈
        if (b[0] != 1)
            st[++top] = b[0];
        // 枚举查询点
        for (int i = 1; i < b.size(); i++)
        {
            int l = hld.lca(st[top], b[i]);
            // 当前链连边，top出栈。维护从根向下的一条链，按深度从小到大存储
            while (top > 1 && hld.dep[st[top - 1]] >= hld.dep[l])
            {
                add(st[top - 1], st[top]);
                top--;
            }
            // lca和top连边，top出栈，lca入栈
            if (l != st[top])
            {
                add(l, st[top]);
                st[top] = l;
            }
            st[++top] = b[i];
        }
        // 对最后一条链连边，top出栈
        while (top > 1)
        {
            add(st[top - 1], st[top]);
            top--;
        }
    };
    vi sz(n + 1);
    int q, res;
    cin >> q;
    auto dp = [&](auto &&dp, int x, int fa) -> void
    {
        if (sz[x]) // x是查询点
        {
            for (auto y : G[x])
            {
                if (y == fa)
                    continue;
                dp(dp, y, x);
                if (sz[y]) // 儿子也是查询点，切断这条边之间的一个点
                {
                    res++;
                    sz[y] = 0;
                }
            }
        }
        else
        {
            for (auto y : G[x])
            {
                if (y == fa)
                    continue;
                dp(dp, y, x);
                sz[x] += sz[y];
                sz[y] = 0;
            }
            // x不是查询点，删除当前点
            if (sz[x] > 1)
            {
                res++;
                sz[x] = 0;
            }
        }
    };
    while (q--)
    {
        res = 0;
        int m;
        cin >> m;
        vi a(m);
        for (auto &x : a)
        {
            cin >> x;
            sz[x] = 1;
            vis.push_back(x);
        }
        bool f = false;
        for (auto &x : a)
        {
            if (sz[hld.fa[x]])
            {
                f = true;
                break;
            }
        }
        if (f)
            print(-1);
        else
        {
            build_virtual_tree(a);
            dp(dp, 1, 0);
            print(res);
        }
        for (auto x : vis)
            sz[x] = 0;
    }
}
