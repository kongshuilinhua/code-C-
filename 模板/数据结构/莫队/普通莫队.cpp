//
// Created by elysia on 2025/5/16.
//
// https://www.luogu.com.cn/problem/P2709
// https://www.luogu.com.cn/problem/P12598
int B = 223;
struct X
{
    int l, r, id;
};
bool cmp(X &a, X &b)
{
    if (a.l / B != b.l / B)
        return a.l < b.l; // 首先按照块号升序
    if ((a.l / B) & 1)
        return a.r < b.r; // 奇数块r升序
    return a.r > b.r;     // 偶数块r降序
}
unordered_map<int, int> cnt;
int sum;
inline void add(const int x)
{
    sum += (cnt[x] << 1 | 1), ++cnt[x];
}
inline void del(const int x)
{
    --cnt[x], sum -= (cnt[x] << 1 | 1);
}
void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    vi a(n + 1);

    vector<X> qrs;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 0; i < m; i++)
    {
        int l, r;
        cin >> l >> r;
        qrs.push_back({l, r, i});
    }
    sort(all(qrs), cmp);
    int l = 1, r = 0;
    vi res(m);
    for (int i = 0; i < m; i++)
    {
        while (l > qrs[i].l)
            add(a[--l]); // 左扩展
        while (r < qrs[i].r)
            add(a[++r]); // 右扩展
        while (l < qrs[i].l)
            del(a[l++]); // 左删除
        while (r > qrs[i].r)
            del(a[r--]); // 右删除
        res[qrs[i].id] = sum;
    }
    for (auto x : res)
        print(x);
}
