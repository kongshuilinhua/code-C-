//
// Created by elysia on 2025/5/26.
//
// https://www.acwing.com/problem/content/1126/
// https://www.luogu.com.cn/problem/P7771
// https://codeforces.com/contest/2110/problem/E
// 返回 0…n-1 节点的欧拉通路，directed=true: 有向图，false: 无向图。
// 若不存在欧拉通路，返回空 vector。
vector<int> findEulerPath(int n,
                          const vector<pair<int, int>> &edges,
                          bool directed = false)
{
    int m = edges.size();
    // 1) 构造邻接表的同时累加度数
    vector<vector<pair<int, int>>> adj(n);
    vector<bool> used(directed ? m : 2 * m, false);
    vector<int> indeg(n), outdeg(n), odd;
    for (int i = 0; i < m; i++)
    {
        int u = edges[i].first, v = edges[i].second;
        if (directed)
        {
            adj[u].emplace_back(v, i);
            outdeg[u]++;
            indeg[v]++;
        }
        else
        {
            adj[u].emplace_back(v, 2 * i);
            adj[v].emplace_back(u, 2 * i + 1);
        }
    }
    // 最小字典序
    // for (int i = 0; i < n; i++) sort(all(adj[i]));
    int start = -1;
    // 2) 度数合法性检查
    if (directed)
    {
        //  所有点的入度等于出度 或者 存在一点出度比入度大1(起点)，一点入度比出度大1(终点)，其他点的入度均等于出度。
        int cnt1 = 0, cnt2 = 0;
        for (int i = 0; i < n; i++)
        {
            if (indeg[i] != outdeg[i])
            {
                if (indeg[i] + 1 == outdeg[i])
                    cnt1++, start = i;
                else if (indeg[i] == outdeg[i] + 1)
                    cnt2++;
                else
                    return {};
            }
        }
        if (!(cnt1 == 0 && cnt2 == 0) && !(cnt1 == 1 && cnt2 == 1))
            return {};
    }
    else
    {
        // 无向图中所有奇度点的数量为0或2。
        for (int i = 0; i < n; i++)
            if (adj[i].size() & 1)
                odd.push_back(i);
        if (odd.size() != 0 && odd.size() != 2)
            return {};
        if (odd.size() > 0)
            start = odd[0];
    }
    // 找个非孤立点
    if (start == -1)
    {
        for (int i = 0; i < n; i++)
        {
            if (!adj[i].empty())
            {
                start = i;
                break;
            }
        }
    }
    if (start == -1)
        return {};
    // 4) Hierholzer 算法
    vector<int> pos(n), ans;

    function<void(int)> dfs = [&](int u)
    {
        while (pos[u] < (int)adj[u].size())
        {
            auto [v, eid] = adj[u][pos[u]++];
            if (used[eid])
                continue;
            used[eid] = true;
            if (!directed)
                used[eid ^ 1] = true;
            dfs(v);
            // 获取边id
//            if (directed)
//                ans.push_back(eid + 1);
//            else
//                ans.push_back(eid / 2 + 1);
        }
        ans.push_back(u);
    };

    dfs(start);
    reverse(ans.begin(), ans.end());
    return ans;
}