// 矩形面积并
const int N = 1e5 + 10;
vi b;
struct X
{
    int cnt, len;
} tr[8 * N];  // 8倍空间
void pushup(int o, int l, int r)
{
    if (tr[o].cnt) // 被完全覆盖，坐标偏移
        tr[o].len = b[r + 1] - b[l];
    else if (l != r) // 不是叶子结点，合并子节点长度
        tr[o].len = tr[lc].len + tr[rc].len;
    else
        tr[o].len = 0;
}
void update(int o, int l, int r, int L, int R, int v)
{
    if (L > r || R < l)
        return;
    if (L <= l && r <= R)
    {
        tr[o].cnt += v;
        pushup(o, l, r);
        return;
    }
    update(lc, l, mid, L, R, v);
    update(rc, mid + 1, r, L, R, v);
    pushup(o, l, r);
}
void solve()
{
    int n;
    cin >> n;
    vector<array<int, 4>> edges;
    for (int i = 0; i < n; i++)
    {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        edges.push_back({x1, y1, y2, 1});
        edges.push_back({x2, y1, y2, -1});
        b.push_back(y1); // 离散化y坐标
        b.push_back(y2);
    }
    sort(all(edges));
    sort(all(b));
    b.erase(unique(all(b)), b.end());
    unordered_map<int, int> mp;
    for (int i = 0; i < b.size(); i++)
        mp[b[i]] = i;
    int x1 = 0, res = 0;
    int m = b.size();
    for (auto [x2, y1, y2, v] : edges)
    {
        res += tr[1].len * (x2 - x1);
        update(1, 0, m, mp[y1], mp[y2] - 1, v); // 向左偏移一个
        x1 = x2;
    }
    print(res);
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    int t = 1;
    // cin >> t;
    while (t--)
        solve();
}
// https://leetcode.cn/problems/rectangle-area-ii/description/
class Solution {
public:
    static const int MOD = 1e9 + 7;
    struct Node { int cnt, len; };
    vector<int> ys;
    vector<Node> st;

    void pushup(int o, int l, int r) {
        if (st[o].cnt > 0) {
            st[o].len = ys[r + 1] - ys[l];
        } else if (l == r) {
            st[o].len = 0;
        } else {
            st[o].len = st[o<<1].len + st[o<<1|1].len;
        }
    }

    void update(int o, int l, int r, int L, int R, int v) {
        if (L > r || R < l) return;
        if (L <= l && r <= R) {
            st[o].cnt += v;
            pushup(o, l, r);
            return;
        }
        int m = (l + r) >> 1;
        update(o<<1,     l,   m, L, R, v);
        update(o<<1|1, m+1,   r, L, R, v);
        pushup(o, l, r);
    }

    int rectangleArea(vector<vector<int>>& rectangles) {
        struct Event { int x, y1, y2, v; };
        vector<Event> events;
        ys.clear();

        for (auto &rec : rectangles) {
            int x1 = rec[0], y1 = rec[1], x2 = rec[2], y2 = rec[3];
            events.push_back({x1, y1, y2, 1});
            events.push_back({x2, y1, y2, -1});
            ys.push_back(y1);
            ys.push_back(y2);
        }

        sort(ys.begin(), ys.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());
        sort(events.begin(), events.end(), [](auto &a, auto &b){ return a.x < b.x; });

        int m = ys.size();
        st.assign(4 * m, {0, 0});

        long ans = 0;
        int prevX = events[0].x;
        for (auto &e : events) {
            ans = (ans + 1LL * (e.x - prevX) * st[1].len) % MOD;
            int l = int(lower_bound(ys.begin(), ys.end(), e.y1) - ys.begin());
            int r = int(lower_bound(ys.begin(), ys.end(), e.y2) - ys.begin()) - 1;
            if (l <= r) update(1, 0, m - 2, l, r, e.v);
            prevX = e.x;
        }

        return int(ans);
    }
};