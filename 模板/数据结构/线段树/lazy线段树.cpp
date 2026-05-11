#define lc o << 1
#define rc o << 1 | 1
#define mid (l + r) / 2

// 区间乘，区间加
int mod;
const int inf = 1e18;
const int N = 1e5 + 10;
// const int mod = 1e9 + 7;
int add[4 * N], sum[4 * N], nums[N], mul[4 * N];
void pushup(int o)
{
    sum[o] = sum[lc] + sum[rc];
    sum[o] %= mod;
}
void calc(int o, int l, int r, int m, int a)
{
    sum[o] = sum[o] * m + (r - l + 1) * a;
    sum[o] %= mod;
    mul[o] = mul[o] * m % mod;
    add[o] = (add[o] * m + a) % mod;
}
void pushdown(int o, int l, int r)
{
    int mid = (l + r) / 2;
    calc(lc, l, mid, mul[o], add[o]);
    calc(rc, mid + 1, r, mul[o], add[o]);
    add[o] = 0;
    mul[o] = 1;
}
void build(int o, int l, int r)
{
    sum[o] = nums[l];
    mul[o] = 1;
    if (l == r)
        return;
    int mid = (l + r) / 2;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    pushup(o);
}

void update(int o, int l, int r, int L, int R, int m, int a)
{
    if (L > r || R < l)
        return;
    if (L <= l && r <= R)
    {
        calc(o, l, r, m, a);
        return;
    }
    pushdown(o, l, r);
    int mid = (l + r) / 2;
    update(lc, l, mid, L, R, m, a);
    update(rc, mid + 1, r, L, R, m, a);
    pushup(o);
}

int query(int o, int l, int r, int L, int R)
{
    if (L > r || R < l)
        return 0;
    if (L <= l && r <= R)
        return sum[o];
    pushdown(o, l, r);
    int mid = (l + r) / 2;
    int res = query(lc, l, mid, L, R) + query(rc, mid + 1, r, L, R);
    return res % mod;
}


// 区间修改为x。区间加x
const int N = 1e6 + 10;
int nums[N];
struct X
{
    int add, mx, cover = inf;
} tr[4 * N];

void pushup(int o)
{
    tr[o].mx = max(tr[lc].mx, tr[rc].mx);
}

void pushdown(int o, int l, int r)
{
    if (tr[o].cover != inf)
    {
        tr[lc].cover = tr[rc].cover = tr[o].cover;
        tr[lc].add = tr[rc].add = 0;
        tr[lc].mx = tr[rc].mx = tr[o].cover;
        tr[o].cover = inf;
    }
    if (tr[o].add)
    {
        tr[lc].add += tr[o].add;
        tr[rc].add += tr[o].add;
        tr[lc].mx += tr[o].add;
        tr[rc].mx += tr[o].add;
        tr[o].add = 0;
    }
}

void build(int o, int l, int r)
{
    tr[o].cover = inf;
    if (l == r)
    {
        tr[o].mx = nums[l];
        return;
    }
    build(lc, l, mid);
    build(rc, mid + 1, r);
    pushup(o);
}

// t = 1 表示区间赋值，t = 2 表示区间加法
void update(int o, int l, int r, int L, int R, int x, int t)
{
    if (L > r || R < l)
        return;
    if (L <= l && r <= R)
    {
        if (t == 1)
        {
            tr[o].cover = x;
            tr[o].add = 0;
            tr[o].mx = x;
        }
        else
        {
            tr[o].add += x;
            tr[o].mx += x;
        }
        return;
    }
    pushdown(o, l, r);
    update(lc, l, mid, L, R, x, t);
    update(rc, mid + 1, r, L, R, x, t);
    pushup(o);
}

ll query(int o, int l, int r, int L, int R)
{
    if (L > r || R < l)
        return -inf;
    if (L <= l && r <= R)
    {
        return tr[o].mx;
    }
    pushdown(o, l, r);
    return max(query(lc, l, mid, L, R),
               query(rc, mid + 1, r, L, R));
}

// 给出一个长度等于 r−l+1 的等差数列，首项为 K，公差为 D，并将它对应加到 [l,r] 范围中的每一个数上。即：令 al=al+k, al+1=al+1+k+D
const int N = 1e5 + 10;
int a[N];
struct X
{
    int sum, lazy;
} tr[4 * N];
void pushup(int o)
{
    tr[o].sum = tr[lc].sum + tr[rc].sum;
}
void build(int o, int l, int r)
{
    if (l == r)
    {
        tr[o].sum = a[l];
        return;
    }
    build(lc, l, mid);
    build(rc, mid + 1, r);
    pushup(o);
}
void pushdown(int o, int l, int r)
{
    tr[lc].lazy += tr[o].lazy;
    tr[rc].lazy += tr[o].lazy;
    tr[lc].sum += (mid - l + 1) * tr[o].lazy;
    tr[rc].sum += (r - mid) * tr[o].lazy;
    tr[o].lazy = 0;
}
void update(int o, int l, int r, int L, int R, int val)
{
    if (L > r || R < l)
        return;
    if (L <= l && r <= R)
    {
        tr[o].sum += (r - l + 1) * val;
        tr[o].lazy += val;
        return;
    }
    pushdown(o, l, r);
    update(lc, l, mid, L, R, val);
    update(rc, mid + 1, r, L, R, val);
    pushup(o);
}
int query(int o, int l, int r, int L, int R)
{
    if (L > r || R < l)
        return 0;
    if (L <= l && r <= R)
    {
        return tr[o].sum;
    }
    pushdown(o, l, r);
    return query(lc, l, mid, L, R) + query(rc, mid + 1, r, L, R);
}
void solve()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = n - 1; i >= 1; i--)
        a[i + 1] -= a[i];
    build(1, 1, n + 1);
    while (m--)
    {
        int op, l, r, k, d, p;
        cin >> op;
        if (op == 1)
        {
            cin >> l >> r >> k >> d;
            update(1, 1, n + 1, l, l, k);
            update(1, 1, n + 1, l + 1, r, d);
            update(1, 1, n + 1, r + 1, r + 1, -(k + (r - l) * d));
        }
        else
        {
            cin >> p;
            print(query(1, 1, n + 1, 1, p));
        }
    }
}


// 区间涂色为c， 查询区间颜色数
struct X
{
    bitset<31> bs;
    int c;
} tr[4 * N];

void pushup(int o)
{
    tr[o].bs = tr[lc].bs | tr[rc].bs;
}

void pushdown(int o, int l, int r)
{
    if (tr[o].c == 0)
        return;
    tr[lc].c = tr[rc].c = tr[o].c;
    tr[lc].bs.reset();
    tr[rc].bs.reset();
    tr[lc].bs[tr[o].c] = tr[rc].bs[tr[o].c] = 1;
    tr[o].c = 0;
}

void build(int o, int l, int r)
{
    if (l == r)
    {
        tr[o].bs[1] = 1;
        return;
    }
    build(lc, l, mid);
    build(rc, mid + 1, r);
    pushup(o);
}

void update(int o, int l, int r, int L, int R, int x)
{
    if (L > r || R < l)
        return;
    if (L <= l && r <= R)
    {
        tr[o].c = x;
        tr[o].bs.reset();
        tr[o].bs[x] = 1;
        return;
    }
    pushdown(o, l, r);
    update(lc, l, mid, L, R, x);
    update(rc, mid + 1, r, L, R, x);
    pushup(o);
}

bitset<31> query(int o, int l, int r, int L, int R)
{
    if (L > r || R < l)
        return 0;
    if (L <= l && r <= R)
    {
        return tr[o].bs;
    }
    pushdown(o, l, r);
    return (query(lc, l, mid, L, R) |
            query(rc, mid + 1, r, L, R));
}

// 单点修改，查询区间最大连续子段值
int a[N];
struct X
{
    int pre, suf, sum, mx;
} tr[4 * N];

void pushup(X &cur, X l, X r)
{
    cur.sum = l.sum + r.sum;
    cur.pre = max(l.pre, l.sum + r.pre);
    cur.suf = max(r.suf, r.sum + l.suf);
    cur.mx = max({l.mx, r.mx, l.suf + r.pre});
}

void build(int o, int l, int r)
{
    tr[o] = {a[l], a[l], a[l], a[l]};
    if (l == r)
    {
        return;
    }
    int mid = (l + r) / 2;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    pushup(tr[o], tr[lc], tr[rc]);
}

void update(int o, int l, int r, int i, int x)
{
    if (i > r || i < l)
        return;
    if (l == r)
    {
        tr[o] = {x, x, x, x};
        return;
    }
    int mid = (l + r) / 2;
    update(lc, l, mid, i, x);
    update(rc, mid + 1, r, i, x);
    pushup(tr[o], tr[lc], tr[rc]);
}

X query(int o, int l, int r, int L, int R)
{
    if (l > R || r < L)
        return {-inf, -inf, 0, -inf};
    if (L <= l && r <= R)
        return tr[o];

    int mid = (l + r) / 2;
    X res;
    pushup(res, query(lc, l, mid, L, R), query(rc, mid + 1, r, L, R));
    return res;
}

// 区间加，区间gcd
struct X
{
    int sum, g;
} tr[4 * N];

void pushup(X &cur, X l, X r)
{
    cur.sum = l.sum + r.sum;
    cur.g = gcd(l.g, r.g);
}

void build(int o, int l, int r)
{
    tr[o] = {a[l], a[l]};
    if (l == r)
    {
        return;
    }
    int mid = (l + r) / 2;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    pushup(tr[o], tr[lc], tr[rc]);
}

void update(int o, int l, int r, int i, int x)
{
    if (i > r || i < l)
        return;
    if (l == r)
    {
        tr[o].sum += x;
        tr[o].g += x;
        return;
    }
    int mid = (l + r) / 2;
    update(lc, l, mid, i, x);
    update(rc, mid + 1, r, i, x);
    pushup(tr[o], tr[lc], tr[rc]);
}

X query(int o, int l, int r, int L, int R)
{
    if (l > R || r < L)
        return {0, 0};
    if (L <= l && r <= R)
        return tr[o];

    int mid = (l + r) / 2;
    X res;
    pushup(res, query(lc, l, mid, L, R), query(rc, mid + 1, r, L, R));
    return res;
}

void solve()
{
    int n, m;
    cin >> n >> m;
    int t, y = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> t;
        a[i] = t - y;
        swap(t, y);
    }
    int l, r, x;
    char op;
    build(1, 1, n + 1);
    while (m--)
    {
        cin >> op;
        if (op == 'C')
        {
            cin >> l >> r >> x;
            update(1, 1, n + 1, l, x);
            update(1, 1, n + 1, r + 1, -x);
        }
        else
        {
            cin >> l >> r;
            X L = query(1, 1, n + 1, 1, l);
            X R = query(1, 1, n + 1, l + 1, r);
            print(abs(gcd(L.sum, R.g)));
        }
    }
}


/*
1 l r ，查询区间[l,r]中最长连续相同字符串并输出该字符串的左右边界，如果有多个，输出左边界最小的那个
2 x ch，将a[x]改为ch，字符串下标从1开始
*/
const int N = 1e5 + 10;
char a[N];
struct X
{
    int L, R;       // 该节点覆盖的区间 [L,R]
    char lc, rc;    // 左/右端字符
    int pre, suf;   // 前缀/后缀连续长度
    int mx;         // 区间内最长连续相同字符长度
    int mx_l, mx_r; // 最长连续段的左右边界
} tr[4 * N];

void pushup(X &cur, const X &l, const X &r)
{
    cur.L = l.L;
    cur.R = r.R;
    cur.lc = l.lc;
    cur.rc = r.rc;
    // 前缀
    cur.pre = l.pre;
    if (l.pre == l.R - l.L + 1 && l.rc == r.lc)
        cur.pre = l.pre + r.pre;
    // 后缀
    cur.suf = r.suf;
    if (r.suf == r.R - r.L + 1 && l.rc == r.lc)
        cur.suf = r.suf + l.suf;
    // 最佳区间
    cur.mx = l.mx;
    cur.mx_l = l.mx_l;
    cur.mx_r = l.mx_r;
    if (r.mx > cur.mx)
    {
        cur.mx = r.mx;
        cur.mx_l = r.mx_l;
        cur.mx_r = r.mx_r;
    }
    // 跨中点段
    if (l.rc == r.lc)
    {
        int len = l.suf + r.pre;
        int left = l.R - l.suf + 1;
        int right = r.L + r.pre - 1;
        if (len > cur.mx || (len == cur.mx && left < cur.mx_l))
        {
            cur.mx = len;
            cur.mx_l = left;
            cur.mx_r = right;
        }
    }
}

void build(int o, int l, int r)
{
    if (l == r)
    {
        tr[o] = {l, r, a[l], a[l], 1, 1, 1, l, r};
        return;
    }
    int m = (l + r) >> 1;
    build(o << 1, l, m);
    build(o << 1 | 1, m + 1, r);
    pushup(tr[o], tr[o << 1], tr[o << 1 | 1]);
}

void update(int o, int l, int r, int i, char x)
{
    if (l == r)
    {
        tr[o] = {l, r, x, x, 1, 1, 1, l, r};
        return;
    }
    int m = (l + r) >> 1;
    if (i <= m)
        update(o << 1, l, m, i, x);
    else
        update(o << 1 | 1, m + 1, r, i, x);
    pushup(tr[o], tr[o << 1], tr[o << 1 | 1]);
}

X query(int o, int l, int r, int L, int R)
{
    if (L <= l && r <= R)
        return tr[o];
    int m = (l + r) >> 1;
    if (R <= m)
        return query(o << 1, l, m, L, R);
    if (L > m)
        return query(o << 1 | 1, m + 1, r, L, R);
    X left = query(o << 1, l, m, L, R);
    X right = query(o << 1 | 1, m + 1, r, L, R);
    X res;
    pushup(res, left, right);
    return res;
}

// 查询区间平方，区间和。区间加

double nums[N];
struct X
{
    double s, sq, add = 0.0;
} tr[4 * N];

void pushup(X &cur, X l, X r)
{
    cur.s = l.s + r.s;
    cur.sq = l.sq + r.sq;
}

void pushdown(int o, int l, int r)
{
    if (tr[o].add)
    {
        tr[lc].add += tr[o].add;
        tr[rc].add += tr[o].add;
        tr[lc].sq += 2 * tr[lc].s * tr[o].add + (mid - l + 1) * tr[o].add * tr[o].add;
        tr[rc].sq += 2 * tr[rc].s * tr[o].add + (r - mid) * tr[o].add * tr[o].add;
        tr[lc].s += (mid - l + 1) * tr[o].add;
        tr[rc].s += (r - mid) * tr[o].add;
        tr[o].add = 0;
    }
}

void build(int o, int l, int r)
{
    if (l == r)
    {
        tr[o].s = nums[l];
        tr[o].sq = nums[l] * nums[l];
        return;
    }
    build(lc, l, mid);
    build(rc, mid + 1, r);
    pushup(tr[o], tr[lc], tr[rc]);
}

void update(int o, int l, int r, int L, int R, double x)
{
    if (L > r || R < l)
        return;
    if (L <= l && r <= R)
    {
        tr[o].add += x;
        tr[o].sq += 2 * tr[o].s * x + (r - l + 1) * x * x;
        tr[o].s += (r - l + 1) * x;
        return;
    }
    pushdown(o, l, r);
    update(lc, l, mid, L, R, x);
    update(rc, mid + 1, r, L, R, x);
    pushup(tr[o], tr[lc], tr[rc]);
}

X query(int o, int l, int r, int L, int R)
{
    if (L > r || R < l)
        return {0, 0, 0};
    if (L <= l && r <= R)
    {
        return tr[o];
    }
    pushdown(o, l, r);
    X res;
    pushup(res, query(lc, l, mid, L, R),
           query(rc, mid + 1, r, L, R));
    return res;
}
