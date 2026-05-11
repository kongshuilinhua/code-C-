//
// Created by elysia on 2025/5/22.
//

// https://www.luogu.com.cn/problem/P3381
const int inf = 1e18;
const int N = 2e5 + 10;
int n, m, S, T;
struct edge
{
    int u, v, cap, w;
};

// 全局变量
vector<edge> e;   // 边集，存储所有正向边和反向边
vector<int> h[N]; // 邻接表：h[u] 存储从 u 出发的所有边在 e 中的下标
int mf[N];        // 起点S-v的流量上限
int pre[N];       // v的前驱边
int d[N], vis[N];
int flow, cost;
void add(int u, int v, int cap, int w)
{
    e.push_back({u, v, cap, w});
    h[u].push_back(e.size() - 1);
}

bool spfa()
{
    fill(&mf[0], &mf[N], 0);
    fill(&d[0], &d[N], inf);
    queue<int> q;
    q.push(S);
    mf[S] = inf;
    d[S] = 0;
    while (!q.empty())
    {
        int x = q.front();
        q.pop();
        vis[x] = 0;
        for (auto i : h[x])
        {
            auto [x, y, cap, w] = e[i];
            if (d[y] > d[x] + w && cap)
            {
                d[y] = d[x] + w;
                pre[y] = i;
                mf[y] = min(mf[x], cap);
                if (!vis[y])
                {
                    q.push(y);
                    vis[y] = 1;
                }
            }
        }
    }
    return mf[T] > 0;
}

void ek()
{
    while (spfa())
    {
        int x = T;
        while (x != S)
        {
            int i = pre[x];
            e[i].cap -= mf[T];
            e[i ^ 1].cap += mf[T];
            x = e[i ^ 1].v;
        }
        flow += mf[T];
        cost += mf[T] * d[T];
    }
}
void solve()
{
    cin >> n >> m >> S >> T;
    for (int i = 0; i < m; i++)
    {
        int u, v, cap, w;
        cin >> u >> v >> cap >> w;
        add(u, v, cap, w);
        add(v, u, 0, -w);
    }
    ek();
    print(flow, cost);
}
