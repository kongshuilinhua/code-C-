//
// Created by elysia on 2025/8/7.
//
// https://www.luogu.com.cn/problem/AT_joisc2014_c
// https://www.luogu.com.cn/problem/P5906
#include <bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(), (x).end()
#define int long long
struct X
{
    int bid, l, r, id;
};

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    // 离散化后会快很多！
    vector<int> s = a;
    sort(all(s));
    s.erase(unique(all(s)), s.end());
    for (int i = 0; i < n; i++)
        b[i] = lower_bound(all(s), a[i]) - s.begin();
    int M = s.size();
    int B = 200;
    vector<X> qrs;
    vector<int> cnt(M, 0);
    // unordered_map<int, int> cnt;
    int mx = 0;
    auto add = [&](int i)
    {
        cnt[b[i]]++;
        mx = max(mx, a[i] * cnt[b[i]]);
    };
    vector<int> res(q);

    for (int i = 0; i < q; i++)
    {
        int l, r;
        cin >> l >> r;
        --l; // 左闭右开[l, r)
        // 大区间离线（保证 l 和 r 不在同一个块中）
        if (r - l > B)
        {
            qrs.push_back({l / B, l, r, i});
        }
        else
        {
            // 小区间暴力（可以直接用哈希表）
            unordered_map<int, int> tmp;
            int best = 0;
            for (int j = l; j < r; j++)
            {
                int v = a[j];
                tmp[v]++;
                best = max(best, tmp[v] * v);
                // cout << tmp[v] << " " << v << "\n";
            }
            res[i] = best;
        }
    }

    sort(qrs.begin(), qrs.end(), [&](auto &A, auto &B)
    {
        if (A.bid != B.bid) return A.bid < B.bid;
        return A.r < B.r; });

    int r = 0;
    for (int i = 0; i < (int)qrs.size(); i++)
    {
        auto &q = qrs[i];
        int l0 = (q.bid + 1) * B;
        // 遍历到一个新的块
        if (i == 0 || q.bid > qrs[i - 1].bid)
        {
            r = l0; // 右端点移动的起点
            // 重置数据
            fill(all(cnt), 0);
            mx = 0;
        }
        // 右端点从 r 移动到 q.r（q.r 不计入）
        for (; r < q.r; r++)
        {
            add(r);
        }
        // 记录数据
        int tmp_mx = mx;
        for (int j = q.l; j < l0; j++)
        {
            add(j);
        }
        res[q.id] = mx;
        // 回滚
        for (int j = q.l; j < l0; j++)
        {
            cnt[b[j]]--;
        }
        mx = tmp_mx;
    }

    for (int x : res)
        cout << x << "\n";
    return 0;
}