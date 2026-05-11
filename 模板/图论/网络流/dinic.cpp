//
// Created by elysia on 2025/5/22.
//
// https://www.luogu.com.cn/problem/P3376
// https://www.acwing.com/problem/content/submission/374/
/*
3 最小点覆盖、最大独立集、最小路径点覆盖(最小路径重复点覆盖)
  最大匹配数 = 最小点覆盖 = 总点数 - 最大独立集 = 总点数 - 最小路径覆盖

匹配/匹配边: 与其他边没有公共节点的一条边, 我们称这条边为一个匹配/匹配边.
匹配点: 匹配边上的点
非匹配点: 不在匹配边上的点
非匹配边: 图中两点之间的边不是匹配边的边
最大匹配(匹配边数量的最大值): 最多连多少条边, 使得所有的边无公共点
⭐增广路(径): 一边的非匹配点到另一边的非匹配点的一条非匹配边和匹配边交替经过的路径.
  通俗:由一个未匹配的顶点开始，经过若干个匹配顶点，最后到达对面集合的一个未匹配顶点的路径，即这条路径将两个不同集合的两个未匹配顶点通过一系列匹配顶点相连。
最小点覆盖问题
定义: 给我们一个图, 从中选出最少的点, 使得图中的每一条边至少有一个顶点被选
在二分图中
    最小点覆盖==最大匹配数
    证A = B
    则需证最小点覆盖A ≥ 最大匹配数B - 最大匹配m-最少要选m个点来覆盖m个边(匹配里两两没有交点)
          最大匹配数B = 最小点覆盖A等号可以成立 -  构造一种方案 --由于最小点覆盖是所有方案的最小值

*/
// O(n^2m)
struct Edge
{
    int to, cap, rev;
};

struct Dinic
{
    int N;
    vector<vector<Edge>> G;
    vector<int> level, ptr;
    Dinic(int n) : N(n), G(n), level(n), ptr(n) {}
    void addEdge(int u, int v, int c)
    {
        G[u].push_back({v, c, (int)G[v].size()});
        G[v].push_back({u, 0, (int)G[u].size() - 1});
    }
    bool bfs(int s, int t)
    {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (auto &e : G[u])
                if (e.cap > 0 && level[e.to] < 0)
                {
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
                }
        }
        return level[t] >= 0;
    }
    int dfs(int u, int t, int f)
    {
        if (u == t || f == 0)
            return f;
        for (int &i = ptr[u]; i < (int)G[u].size(); i++)
        {
            auto &e = G[u][i];
            if (e.cap > 0 && level[e.to] == level[u] + 1)
            {
                int pushed = dfs(e.to, t, min(f, e.cap));
                if (pushed)
                {
                    e.cap -= pushed;
                    G[e.to][e.rev].cap += pushed;
                    return pushed;
                }
            }
        }
        return 0;
    }
    int maxflow(int s, int t)
    {
        int flow = 0;
        while (bfs(s, t))
        {
            fill(ptr.begin(), ptr.end(), 0);
            while (int pushed = dfs(s, t, INT_MAX))
                flow += pushed;
        }
        return flow;
    }
};
