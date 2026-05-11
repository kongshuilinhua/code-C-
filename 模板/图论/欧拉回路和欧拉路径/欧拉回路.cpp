//
// Created by elysia on 2025/5/25.
//
// https://www.acwing.com/problem/content/1186/
/*
无向图G存在欧拉路径与欧拉回路的充要条件分别是：
欧拉路径： 图中所有奇度点的数量为0或2。
欧拉回路： 图中所有点的度数都是偶数。

有向图H存在欧拉路径和欧拉回路的充要条件分别是：
欧拉路径： 所有点的入度等于出度 或者 存在一点出度比入度大1(起点)，一点入度比出度大1(终点)，其他点的入度均等于出度。
欧拉回路：所有点的入度等于出度。
 */

void solve()
{
    int type, n, m;
    cin >> type >> n >> m;
    // type 1: 无向图 2： 有向图
    // 用 pair<邻点, 边 id> 来存图
    vvpii g(n + 1);
    vi din(n + 1), dout(n + 1);
    int idx = 0;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        if (type == 1)
        {
            // 无向图：两条有向边，边 id 成对使用
            g[u].emplace_back(v, idx);
            g[v].emplace_back(u, idx ^ 1);
            idx += 2;
        }
        else
        {
            // 有向图：一条有向边
            g[u].emplace_back(v, idx);
            idx++;
        }
        din[v]++;
        dout[u]++;
    }
    if (type == 1)
    {
        // 无向图含欧拉回路的充要条件是每个点的度都为偶数
        for (int i = 1; i <= n; i++)
            if ((din[i] + dout[i]) & 1)
                return print("NO");
    }
    else
    {
        // 有向图含欧拉回路的充要条件是每个点的入度等于出度
        for (int i = 1; i <= n; i++)
            if (din[i] != dout[i])
                return print("NO");
    }
    // Hierholzer 算法
    vi used(idx, 0);
    vi pos(n + 1, 0), ans;
    function<void(int)> dfs = [&](int u)
    {
        auto &i = pos[u];
        while (i < (int)g[u].size())
        {
            auto [v, eid] = g[u][i++];
            if (used[eid])
                continue;
            // 标记使用过，无向边反边也要标记
            used[eid] = 1;
            if (type == 1)
                used[eid ^ 1] = 1;
            dfs(v);
            int t;
            if (type == 1)
            {
                t = eid / 2 + 1;
                if (eid & 1)
                    t = -t;
            }
            else
            {
                t = eid + 1;
            }
            ans.push_back(t);
        }
    };
    // 找一个有出边的起点
    int start = 1;
    for (int i = 1; i <= n; i++)
        if (!g[i].empty())
        {
            start = i;
            break;
        }
    dfs(start);
    if ((int)ans.size() < m)
        return print("NO");
    print("YES");
    reverse(all(ans));
    print(ans);
}
