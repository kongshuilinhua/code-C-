# KD树
```c++
//
// Created by elysia on 2025/5/14.
//
// https://www.luogu.com.cn/problem/P1429  平面最近点对
#define lc t[p].l
#define rc t[p].r
const int N = 2e5 + 10;
double ans = 2e18;
int n, K, root, cur; // K维度,root根,cur当前节点
struct KD
{                      // KD树节点信息
    int l, r;          // 左右孩子
    double v[2];       // 点的坐标值x,y
    double L[2], U[2]; // 子树区域的坐标范围L是x,y的最小值,U是x,y的最大值
    bool operator<(const KD &b) const { return v[K] < b.v[K]; }
} t[N];
// 更新p子树区域的坐标范围
void pushup(int p)
{
    for (int i = 0; i < 2; i++)
    {
        t[p].L[i] = t[p].U[i] = t[p].v[i];
        if (lc)
            t[p].L[i] = min(t[p].L[i], t[lc].L[i]),
                    t[p].U[i] = max(t[p].U[i], t[lc].U[i]);
        if (rc)
            t[p].L[i] = min(t[p].L[i], t[rc].L[i]),
                    t[p].U[i] = max(t[p].U[i], t[rc].U[i]);
    }
}
// 交替建树 O(nlogn)  op为0按照x切分,1按照y切分
int build(int l, int r, int op)
{
    if (l > r)
        return 0;
    int m = (l + r) >> 1;
    K = op;
    nth_element(t + l, t + m, t + r + 1); // 中位数
    t[m].l = build(l, m - 1, op ^ 1);
    t[m].r = build(m + 1, r, op ^ 1);
    pushup(m);
    return m;
}

// 当前点到p点的距离（按需要修改）
double dis(int p)
{
    double s = 0;
    for (int i = 0; i < 2; i++)
        s += sq(t[cur].v[i] - t[p].v[i]);
    return s;
}

// 当前点到p子树区域的最小距离
int dis_min(int p)
{
    if (!p)
        return 2e18;
    int s = 0;
    for (int i = 0; i < 2; ++i)
        s += abs(max(t[cur].v[i] - t[p].U[i], 0LL)) +
             abs(max(t[p].L[i] - t[cur].v[i], 0LL));
    return s;
}

// 当前点到p子树区域的最大距离
int dis_max(int p)
{
    if (!p)
        return 0;
    int s = 0;
    for (int i = 0; i < 2; ++i) // 当前点和左子树的左边界，和右子树的右边界
        s += abs(max(t[cur].v[i] - t[p].L[i], 1ll * 0)) +
             abs(max(t[p].U[i] - t[cur].v[i], 1ll * 0));
    return s;
}

// 查询当前点的最小距离 时间复杂度根号n
void query_min(int p)
{
    if (!p)
        return;
    if (p != cur)
        ans = min(ans, dis(p));
    int dl = dis_min(lc), dr = dis_min(rc);
    if (dl < dr)
    {
        if (dl < ans)
            query_min(lc);
        if (dr < ans)
            query_min(rc);
    }
    else
    {
        if (dr < ans)
            query_min(rc);
        if (dl < ans)
            query_min(lc);
    }
}

// 查询当前点的最大距离
void query_max(int p)
{
    if (!p)
        return;
    if (p != cur)
        ans2 = max(ans2, dis(p));
    int dl = dis_max(lc), dr = dis_max(rc);
    if (dl > dr)
    {
        if (dl > ans2)
            query_max(lc);
        if (dr > ans2)
            query_max(rc);
    }
    else
    {
        if (dr > ans2)
            query_max(rc);
        if (dl > ans2)
            query_max(lc);
    }
}

void solve()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> t[i].v[0] >> t[i].v[1];
    root = build(1, n, 0);
    for (cur = 1; cur <= n; cur++)
        query_min(root);
    cout << fixed << setprecision(4) << sqrtl(ans);
}

//-----------------------------------------------------------------
// 插入删除重构建树

#define lc t[p].l
#define rc t[p].r
const double A = 0.7; // 重构常数
const int N = 200010;
double ans = 2e18;
int n, K, root, cur; // K维度,root根,cur当前节点
int g[N], cnt;       // g存储节点的编号
struct KD
{                      // KD树节点信息
    int l, r;          // 左右孩子
    double v[2];       // 点的坐标值
    double L[2], U[2]; // 子树区域坐标极值
    int siz;           // 子树大小
} t[N];
// 更新p子树的信息
void pushup(int p)
{
    t[p].siz = t[lc].siz + t[rc].siz + 1;
    for (int i = 0; i < 2; i++)
    {
        t[p].L[i] = t[p].U[i] = t[p].v[i];
        if (lc)
            t[p].L[i] = min(t[p].L[i], t[lc].L[i]),
                    t[p].U[i] = max(t[p].U[i], t[lc].U[i]);
        if (rc)
            t[p].L[i] = min(t[p].L[i], t[rc].L[i]),
                    t[p].U[i] = max(t[p].U[i], t[rc].U[i]);
    }
}
// 按点的坐标值比较
bool cmp(int a, int b)
{
    return t[a].v[K] < t[b].v[K];
}
// 重构子树
int rebuild(int l, int r, int k)
{
    if (l > r)
        return 0;
    int m = (l + r) >> 1;
    K = k;
    nth_element(g + l, g + m, g + r + 1, cmp);
    t[g[m]].l = rebuild(l, m - 1, k ^ 1);
    t[g[m]].r = rebuild(m + 1, r, k ^ 1);
    pushup(g[m]);
    return g[m];
}
// 提取p子树的节点编号
void dfs(int p)
{
    if (!p)
        return;
    g[++cnt] = p;
    dfs(lc);
    dfs(rc);
}
// 检查
void check(int &p, int k)
{
    if (A * t[p].siz < max(t[lc].siz, t[rc].siz))
        cnt = 0, dfs(p), p = rebuild(1, cnt, k);
}
// 插点
void insert(int &p, int k)
{
    if (!p)
    {
        p = cur;
        pushup(p);
        return;
    }
    insert(t[cur].v[k] <= t[p].v[k] ? lc : rc, k ^ 1);
    pushup(p);
    check(p, k); // 检查是否重构p子树
}

// 删除当前点（cur）并在必要时重构
void remove(int &p, int k)
{
    if (!p) return;
    // 找到要删的节点
    if (t[p].v[0] == t[cur].v[0] && t[p].v[1] == t[cur].v[1])
    {
        // 收集左右子树所有节点，不包括 p 自身
        cnt = 0;
        int a = t[p].l, b = t[p].r;
        dfs(a);
        dfs(b);
        // 重建子树
        p = rebuild(1, cnt, k);
        return;
    }
    // 继续往下找
    if (t[cur].v[k] <= t[p].v[k])
        remove(t[p].l, k ^ 1);
    else
        remove(t[p].r, k ^ 1);
    // 回溯时更新并检查是否失衡
    pushup(p);
    check(p, k);
}

double sq(double x) { return x * x; }
// 当前点到p点的距离
double dis(int p)
{
    double s = 0;
    for (int i = 0; i < 2; i++)
        s += sq(t[cur].v[i] - t[p].v[i]);
    return s;
}
// 当前点到p子树区域的最小距离
double dis2(int p)
{
    if (!p)
        return 2e18;
    double s = 0;
    for (int i = 0; i < 2; ++i)
        s += sq(max(t[cur].v[i] - t[p].U[i], 0.0)) +
             sq(max(t[p].L[i] - t[cur].v[i], 0.0));
    return s;
}
// 查询当前点的最小距离
void query(int p)
{
    if (!p)
        return;
    if (p != cur)
        ans = min(ans, dis(p));
    double dl = dis2(lc), dr = dis2(rc);
    if (dl < dr)
    {
        if (dl < ans)
            query(lc);
        if (dr < ans)
            query(rc);
    }
    else
    {
        if (dr < ans)
            query(rc);
        if (dl < ans)
            query(lc);
    }
}
void solve()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> t[i].v[0] >> t[i].v[1];
    for (cur = 1; cur <= n; cur++)
    {
        insert(root, 0);
        query(root);
    }
    cout << fixed << setprecision(4) << sqrtl(ans);
}

// -------------------------------------------
// https://www.luogu.com.cn/problem/P4357
// K远点对
// 其余内容同上
// 当前点到p子树区域的最大距离
int dis2(int p)
{
    if (!p)
        return 0;
    int s = 0;
    for (int i = 0; i < 2; ++i)  //当前点和左子树的左边界，和右子树的右边界
        s += sq(max(t[cur].v[i] - t[p].L[i], 1ll * 0)) +
             sq(max(t[p].U[i] - t[cur].v[i], 1ll * 0));
    return s;
}
// 查询当前点的k远点对距离
void query(int p)
{
    if (!p || p == cur)
        return;
    int d = dis(p);
    if (h.size() < cnt)
        h.push(d);
    else
    {
        if (d > h.top())
        {
            h.pop();
            h.push(d);
        }
    }
    int dl = dis2(lc), dr = dis2(rc);
    int ans = h.top();
    if (dl > dr)
    {
        if (dl > ans)
            query(lc);
        if (dr > ans)
            query(rc);
    }
    else
    {
        if (dr > ans)
            query(rc);
        if (dl > ans)
            query(lc);
    }
}
void solve()
{
    int n;
    cin >> n >> cnt;
    cnt *= 2; // 每个点算了两次
    for (int i = 1; i <= n; i++)
        cin >> t[i].v[0] >> t[i].v[1];
    root = build(1, n, 0);
    for (cur = 1; cur <= n; cur++)
        query(root);
    print(h.top());
}
// -------------------------------------------------
// n <= 5e5, op1点(x,y)加上w，op2查询区域内点的权值和。强制在线
// https://www.luogu.com.cn/problem/P4148
#define lc t[p].l
#define rc t[p].r
#define y1 qwq

const double A = 0.7; // 重构常数
const int N = 200010;
int n, op, x1, x2, y1, y2, ans;
int K, root, cur; // K维度,root根,cur当前节点
int g[N], cnt;    // g存储节点的编号
struct KD
{                   // KD树节点信息
    int l, r;       // 左右孩子
    int v[2], w;    // 点的坐标值,点权
    int L[2], U[2]; // 子树区域的坐标范围
    int siz, sum;   // 子树大小,子树和
} t[N];
// 更新p子树的信息
void pushup(int p)
{
    t[p].siz = t[lc].siz + t[rc].siz + 1;
    t[p].sum = t[lc].sum + t[rc].sum + t[p].w;
    for (int i = 0; i < 2; i++)
    {
        t[p].L[i] = t[p].U[i] = t[p].v[i];
        if (lc)
            t[p].L[i] = min(t[p].L[i], t[lc].L[i]),
                    t[p].U[i] = max(t[p].U[i], t[lc].U[i]);
        if (rc)
            t[p].L[i] = min(t[p].L[i], t[rc].L[i]),
                    t[p].U[i] = max(t[p].U[i], t[rc].U[i]);
    }
}
bool cmp(int a, int b)
{ // 按点的坐标值比较
    return t[a].v[K] < t[b].v[K];
}
int rebuild(int l, int r, int k)
{ // 重构子树
    if (l > r)
        return 0;
    int m = (l + r) >> 1;
    K = k;
    nth_element(g + l, g + m, g + r + 1, cmp);
    t[g[m]].l = rebuild(l, m - 1, k ^ 1);
    t[g[m]].r = rebuild(m + 1, r, k ^ 1);
    pushup(g[m]);
    return g[m];
}
// 提取p子树的节点编号
void dfs(int p)
{
    if (!p)
        return;
    g[++cnt] = p;
    dfs(lc);
    dfs(rc);
}
// 检查
void check(int &p, int k)
{
    if (A * t[p].siz < max(t[lc].siz, t[rc].siz))
        cnt = 0, dfs(p), p = rebuild(1, cnt, k);
}
// 插点
void insert(int &p, int k)
{
    if (!p)
    {
        p = cur;
        pushup(p);
        return;
    }
    insert(t[cur].v[k] <= t[p].v[k] ? lc : rc, k ^ 1);
    pushup(p);
    check(p, k); // 检查是否重构p子树
}
// 查询区域数字和
int query(int p)
{
    if (!p || x2 < t[p].L[0] || x1 > t[p].U[0] || // 不相交
        y2 < t[p].L[1] || y1 > t[p].U[1])
        return 0;
    if (x1 <= t[p].L[0] && t[p].U[0] <= x2 && // 完全覆盖
        y1 <= t[p].L[1] && t[p].U[1] <= y2)
        return t[p].sum;
    int res = 0;
    if (x1 <= t[p].v[0] && t[p].v[0] <= x2 && // 部分覆盖
        y1 <= t[p].v[1] && t[p].v[1] <= y2)
        res += t[p].w;
    return query(lc) + query(rc) + res;
}
void solve()
{
    int n, op;
    cin >> n;
    while (cin >> op && op != 3)
    {
        if (op == 1)
        {
            cur++;
            cin >> t[cur].v[0] >> t[cur].v[1] >> t[cur].w;
            t[cur].v[0] ^= ans;
            t[cur].v[1] ^= ans;
            t[cur].w ^= ans;
            insert(root, 0);
        }
        else
        {
            cin >> x1 >> y1 >> x2 >> y2;
            x1 ^= ans;
            y1 ^= ans;
            x2 ^= ans;
            y2 ^= ans;
            ans = query(root);
            print(ans);
        }
    }
}
```