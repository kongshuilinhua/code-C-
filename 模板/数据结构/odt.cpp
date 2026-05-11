//
// Created by elysia on 2026/5/1.
//
// ODT / 珂朵莉树节点
// 表示一段区间 [l, r]，这段区间内所有位置的值都是 v
struct Node
{
    int l, r;
    mutable int v;
    // mutable：因为 set 中的元素默认不能修改
    Node(int l, int r = 0, int v = 0) : l(l), r(r), v(v) {}
    // set 按左端点 l 排序
    bool operator<(const Node &a) const
    {
        return l < a.l;
    }
};

set<Node> odt;

// split(x)：把包含 x 的区间切开，并返回左端点为 x 的区间迭代器(第二个)
auto split(int x)
{
    auto it = odt.lower_bound(Node(x));

    // 如果已经存在一个区间左端点就是 x，直接返回
    if (it != odt.end() && it->l == x)
        return it;
    // 如果 x 在所有区间的左边，无法切，直接返回 begin()
    if (it == odt.begin())
        return it;
    // 看 x 左边的那个区间
    --it;
    // 如果这个区间右端点 < x，说明 x 在两个区间之间的空地里
    if (it->r < x)
        return next(it);
    // 否则说明 x 在当前区间 [l, r] 内部，需要切开
    int l = it->l, r = it->r, v = it->v;
    // 删除原区间 [l, r]
    odt.erase(it);
    // 插入左半段 [l, x - 1]
    odt.insert(Node(l, x - 1, v));
    // 插入右半段 [x, r]，并返回它的迭代器
    return odt.insert(Node(x, r, v)).first;
}

// 区间加：把 [l, r] 中每个位置的值都加 v
void add(int l, int r, int v)
{
    if (l > r) return;
    auto itr = split(r + 1);
    auto itl = split(l);
    for (auto it = itl; it != itr; ++it)
    {
        it->v += v;
    }
}

// 区间赋值：把 [l, r] 中每个位置的值都改成 v
void assign(int l, int r, int v)
{
    if (l > r) return;
    auto itr = split(r + 1);
    auto itl = split(l);
    odt.erase(itl, itr);
    odt.insert(Node(l, r, v));
}

// 查询 [l, r] 中第 k 小的数
int kth(int l, int r, int k)
{
    auto itr = split(r + 1);
    auto itl = split(l);

    vector<pair<int, int>> t;
    for (auto it = itl; it != itr; ++it)
    {
        t.push_back({it->v, it->r - it->l + 1});
    }

    // 按值排序
    sort(t.begin(), t.end());
    // 依次扣掉出现次数，找到第 k 小
    for (auto [val, cnt] : t)
    {
        k -= cnt;
        if (k <= 0)
        {
            return val;
        }
    }
    return -1;
}

// 快速幂：计算 a^b mod mod
int pow(int a, int b, int mod)
{
    int res = 1;
    a %= mod;

    while (b)
    {
        if (b & 1)
        {
            res = res * a % mod;
        }

        a = a * a % mod;
        b >>= 1;
    }

    return res;
}

// 查询区间幂和：
int query_sum(int l, int r, int x, int y)
{
    auto itr = split(r + 1);
    auto itl = split(l);

    int res = 0;

    for (auto it = itl; it != itr; ++it)
    {
        int len = it->r - it->l + 1;
        res = (res + len * pow(it->v, x, y)) % y;
    }

    return res;
}