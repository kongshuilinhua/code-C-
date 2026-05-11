//
// Created by elysia on 2025/5/22.
//
// https://www.luogu.com.cn/problem/P3376
const int N = 2e5 + 10;
int n, m, S, T;
struct edge
{
    int u, v, cap;
};

// 全局变量
vector<edge> e;   // 边集，存储所有正向边和反向边
vector<int> h[N]; // 邻接表：h[u] 存储从 u 出发的所有边在 e 中的下标
int mf[N];        // 起点S-v的流量上限
int pre[N];       // v的前驱边
void add(int u, int v, int cap)
{
    e.push_back({u, v, cap});
    h[u].push_back(e.size() - 1);
}

bool bfs()
{
    fill(&mf[0], &mf[N], 0);
    queue<int> q;
    q.push(S);
    mf[S] = inf;
    while (!q.empty())
    {
        int x = q.front();
        q.pop();
        for (auto i : h[x])
        {
            auto [x, y, cap] = e[i];
            if (mf[y] == 0 && cap)
            {
                mf[y] = min(mf[x], cap);
                pre[y] = i;
                q.push(y);
                if (y == T)
                    return true;
            }
        }
    }
    return false;
}

int ek()
{
    int flow = 0;
    while (bfs())
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
    }
    return flow;
}
void solve()
{
    cin >> n >> m >> S >> T;
    for (int i = 0; i < m; i++)
    {
        int u, v, cap;
        cin >> u >> v >> cap;
        add(u, v, cap);
        add(v, u, 0);
    }
    print(ek());
}
