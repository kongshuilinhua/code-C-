//
// Created by elysia on 2025/5/22.
//
// https://www.luogu.com.cn/problem/P1344
const int N = 2e5 + 10;
int n, m, S, T;
struct edge
{
    int u, v, cap;
};
vector<edge> e;   // 边集，存储所有正向边和反向边
vector<int> h[N]; // 邻接表：h[u] 存储从 u 出发的所有边在 e 中的下标
int d[N];         // 分层图中每个点的深度
int cur[N];       // 当前弧优化：记录 DFS 时已尝试过的边，避免重复扫描
int vis[N];       // 找最小割划分时标记
void add(int u, int v, int cap)
{
    e.push_back({u, v, cap});
    h[u].push_back(e.size() - 1);
}

bool bfs()
{
    // 对点分层
    fill(&d[0], &d[N], 0);
    queue<int> q;
    q.push(S);
    d[S] = 1;
    while (!q.empty())
    {
        int x = q.front();
        q.pop();
        for (int i = 0; i < h[x].size(); i++)
        {
            int j = h[x][i];
            int y = e[j].v;
            // 如果 y 尚未分层且剩余容量 > 0
            if (d[y] == 0 && e[j].cap)
            {
                d[y] = d[x] + 1;
                q.push(y);
                if (y == T)
                    return true;
            }
        }
    }
    return false;
}
// 在分层图上寻找增广路并返回实际送出的流量
int dfs(int x, int mf)
{
    if (x == T)
        return mf; // 到达汇点，返回可推送的流量
    int sum = 0;   // 累计流出的流量
    // 从当前弧 cur[x] 开始尝试，避免重复扫描
    for (int i = cur[x]; i < h[x].size(); i++)
    {
        cur[x] = i;
        int j = h[x][i];
        int y = e[j].v;
        // 只沿分层边且有剩余容量
        if (d[y] == d[x] + 1 && e[j].cap)
        {
            int f = dfs(y, min(e[j].cap, mf));
            // 更新正/反向边的剩余容量
            e[j].cap -= f;
            e[j ^ 1].cap += f;
            sum += f;
            mf -= f;
            if (mf == 0) // 余量优化：本次调用流量用完即退出
                break;
        }
    }
    // 残支优化：如果 x 在所有出边上都没增广成功，可从分层图中删除
    if (sum == 0)
        d[x] = 0;
    return sum;
}
int dinic()
{
    int flow = 0;
    while (bfs())
    {
        fill(&cur[0], &cur[N], 0);
        flow += dfs(S, 1e9);
    }
    return flow;
}
// 标记源侧可达点
void mincut(int x)
{
    // vis[i]=1则属于集合S，否则属于集合T
    vis[x] = 1;
    for (auto y : h[x])
    {
        auto [u, v, cap] = e[y];
        if (!vis[v] && cap)
        {
            mincut(v);
        }
    }
}
void solve()
{
    cin >> n >> m;
    S = 1, T = n;
    vpii edges;
    for (int i = 0; i < m; i++)
    {
        int u, v, cap;
        cin >> u >> v >> cap;
        add(u, v, cap);
        add(v, u, 0);
        edges.push_back({u, v});
    }
    cout << dinic() << " ";

    // 求最小割的最少边数
    h->clear();
    for (auto [u, v] : edges)
    {
        add(u, v, 1);
        add(v, u, 0);
    }
    print(dinic());
}
