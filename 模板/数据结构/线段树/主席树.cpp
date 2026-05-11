// https://www.luogu.com.cn/problem/P3834

struct PersistentSegTree
{
    struct X
    {
        int32_t l, r, cnt;
        long long sum;
    };

    vector<X> tree;
    vector<int> root;
    int32_t cnt;
    vector<int> vals; // 离散化后的数据
    int m;

    PersistentSegTree(const vector<int> &a)
    {
        cnt = 0;
        int n = a.size();

        tree.resize(n << 5);
        root.resize(n);

        // 2. 离散化 (a[0] 不处理，从 a[1] 开始)
        vals.assign(a.begin() + 1, a.end());
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
        m = vals.size();

        root[0] = build(1, m);

        for (int i = 1; i < n; ++i)
        {
            int rk = lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin() + 1;
            root[i] = update(root[i - 1], 1, m, rk, a[i]);
        }
    }

    // 查询区间 [L, R] 的第 k 小值，返回原始数值
    int query_kth(int L, int R, int k)
    {
        int idx = kth(root[L - 1], root[R], 1, m, k);
        return vals[idx - 1];
    }

    // 查询区间 [L, R] 中排名 <= k 的 {数量, 和}
    // k 是排名 rank，不是原始值
    pair<int, long long> query_rank_info(int L, int R, int k)
    {
        return query_cnt_sum(root[L - 1], root[R], 1, m, k);
    }

    // 查询排名 <= k 的 cnt 和 sum
    pair<int, long long> query_cnt_sum(int ql, int qr, int l, int r, int k)
    {
        if (r <= k)
        {
            return {tree[qr].cnt - tree[ql].cnt, tree[qr].sum - tree[ql].sum};
        }
        int mid = (l + r) >> 1;
        pair<int, long long> res = query_cnt_sum(tree[ql].l, tree[qr].l, l, mid, k);
        if (k > mid)
        {
            pair<int, long long> res2 = query_cnt_sum(tree[ql].r, tree[qr].r, mid + 1, r, k);
            res.first += res2.first;
            res.second += res2.second;
        }
        return res;
    }

    int build(int l, int r)
    {
        int cur = ++cnt;
        tree[cur].cnt = 0;
        tree[cur].sum = 0;
        if (l == r)
            return cur;
        int mid = (l + r) >> 1;
        tree[cur].l = build(l, mid);
        tree[cur].r = build(mid + 1, r);
        return cur;
    }

    void pushup(int o)
    {
        tree[o].cnt = tree[tree[o].l].cnt + tree[tree[o].r].cnt;
        tree[o].sum = tree[tree[o].l].sum + tree[tree[o].r].sum;
    }

    int update(int pre, int l, int r, int k, int val)
    {
        int cur = ++cnt;
        if (cur >= tree.size())
            tree.resize(tree.size() * 2);

        tree[cur] = tree[pre];
        if (l == r)
        {
            tree[cur].cnt++;
            tree[cur].sum += val;
            return cur;
        }
        int mid = (l + r) >> 1;
        if (k <= mid)
            tree[cur].l = update(tree[pre].l, l, mid, k, val);
        else
            tree[cur].r = update(tree[pre].r, mid + 1, r, k, val);
        pushup(cur);
        return cur;
    }

    int kth(int ql, int qr, int l, int r, int k)
    {
        if (l == r)
            return l;
        int left_cnt = tree[tree[qr].l].cnt - tree[tree[ql].l].cnt;
        int mid = (l + r) >> 1;
        if (k <= left_cnt)
            return kth(tree[ql].l, tree[qr].l, l, mid, k);
        else
            return kth(tree[ql].r, tree[qr].r, mid + 1, r, k - left_cnt);
    }
};


class ChairmanTree
{
public:
    const static int N = 2e5 + 7;

    int b[N], len;

    struct Seg_Tree
    {
        int lc, rc, sum;
    } T[N << 5];

    int cnt, rot[N];

    void insert(int last, int &i, int l, int r, int k)
    {
        T[i = ++cnt] = T[last];
        T[i].sum++;
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        if (k <= mid)
            insert(T[last].lc, T[i].lc, l, mid, k);
        else
            insert(T[last].rc, T[i].rc, mid + 1, r, k);
    }

    void build(int *be, int *ed)
    {
        for (int *i = be; i != ed; i++)
            b[++len] = *i;
        sort(b + 1, b + len + 1);
        len = unique(b + 1, b + len + 1) - b - 1;
        for (int *i = be, j = 1; i != ed; i++, j++)
        {
            int t = lower_bound(b + 1, b + 1 + len, *i) - b;
            insert(rot[j - 1], rot[j], 1, len, t);
        }
    }

    int ask(int x, int y, int l, int r, int k)
    {
        if (l == r)
            return b[l];
        int mid = (l + r) >> 1;
        int sum = T[T[y].lc].sum - T[T[x].lc].sum;
        if (k <= sum)
            return ask(T[x].lc, T[y].lc, l, mid, k);
        return ask(T[x].rc, T[y].rc, mid + 1, r, k - sum);
    }

    int ask(int l, int r, int k) { return ask(rot[l - 1], rot[r], 1, len, k); }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> a[i], b[i] = a[i];
    sort(b + 1, b + 1 + n);
    int len = unique(b + 1, b + n + 1) - b - 1; // 离散化后的数组长度
    T[0] = build(1, len);
    for (int i = 1; i <= n; i++)
    {
        int t = lower_bound(b + 1, b + 1 + len, a[i]) - b;
        T[i] = update(T[i - 1], 1, len, t);
    }
    for (int i = 0; i < m; i++)
    {
        int l, r, k;
        cin >> l >> r >> k;
        int res = query(T[l - 1], T[r], 1, len, k);
        cout << b[res] << "\n";
    }
    return 0;
}

// https://codeforces.com/gym/102770
// 前K大的和
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 1e5 + 10;
int a[maxn], b[maxn];
int T[maxn], c[maxn * 30], lson[maxn * 30], rson[maxn * 30];
ll sum[maxn * 30], f[maxn];
int tot, t, r, l, k, n, m, q;

int build(int l, int r)
{
    int rt = tot++;
    sum[rt] = 0;
    c[rt] = 0;
    if (l != r)
    {
        int mid = (l + r) >> 1;
        lson[rt] = build(l, mid);
        rson[rt] = build(mid + 1, r);
    }
    return rt;
}

int update(int pre, int l, int r, int pos, int val)
{
    int rt = tot++;
    lson[rt] = lson[pre];
    rson[rt] = rson[pre];
    c[rt] = c[pre] + val;
    sum[rt] = sum[pre] + b[pos];
    if (l != r)
    {
        int mid = (l + r) >> 1;
        if (pos <= mid)
            lson[rt] = update(lson[pre], l, mid, pos, val);
        else
            rson[rt] = update(rson[pre], mid + 1, r, pos, val);
    }
    return rt;
}

ll query(int lr, int rr, int l, int r, int k)
{
    if (l == r)
        return b[l] * k;
    int rsum = c[rson[rr]] - c[rson[lr]];
    int mid = (l + r) >> 1;
    if (rsum >= k)
        return query(rson[lr], rson[rr], mid + 1, r, k);
    else
        return sum[rson[rr]] - sum[rson[lr]] + query(lson[lr], lson[rr], l, mid, k - rsum);
}

int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    for (int i = 1; i <= 100000; ++i)
        f[i] = (ll)i * i + f[i - 1];
    cin >> t;
    while (t--)
    {
        tot = 0;
        cin >> n;
        for (int i = 1; i <= n; ++i)
        {
            cin >> a[i];
            b[i] = a[i];
        }
        sort(b + 1, b + 1 + n);
        m = unique(b + 1, b + 1 + n) - b - 1;
        T[0] = build(1, m);
        for (int i = 1; i <= n; ++i)
        {
            int pos = lower_bound(b + 1, b + 1 + m, a[i]) - b;
            T[i] = update(T[i - 1], 1, m, pos, 1);
        }
        cin >> q;
        while (q--)
        {
            cin >> l >> r >> k;
            cout << (query(T[l - 1], T[r], 1, m, k) + f[r - l + 1]) << "\n";
        }
    }
    return 0;
}

