#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl "\n"
#define all(x) (x).begin(), (x).end()
constexpr int N = 1e5 + 5;
int n, opt, l, r, c, len;
int a[N], id[N], lazy[N];
set<int> s[105];

void add(int l, int r, int x) {
    int sid = id[l], eid = id[r];

    // 单独的非整块直接暴力修改
    for (int i = l; i <= min(sid * len, r); i++) {
        s[sid].erase(a[i]);
        a[i] += x;
        s[sid].insert(a[i]);
    }

    // 右边有非整块直接暴力修改
    if (sid != eid) {
        for (int i = (eid - 1) * len + 1; i <= r; i++) {
            s[eid].erase(a[i]);
            a[i] += x;
            s[eid].insert(a[i]);
        }
    }

    // 整块打上标记
    for (int i = sid + 1; i < eid; i++)
        lazy[i] += x;
}

int query(int l, int r, int x) {
    int res = -1;
    int sid = id[l], eid = id[r];

    // 左边非整块暴力计算
    for (int i = l; i <= min(sid * len, r); i++)
        if (a[i] + lazy[sid] < x)
            res = max(res, a[i] + lazy[sid]);

    // 右边非整块暴力计算
    if (sid != eid) {
        for (int i = (eid - 1) * len + 1; i <= r; i++)
            if (a[i] + lazy[eid] < x)
                res = max(res, a[i] + lazy[eid]);
    }

    // 整块内二分 a[i] + lazy[i] < x
    for (int i = sid + 1; i < eid; i++) {
        int t = x - lazy[i];
        set<int>::iterator it = s[i].lower_bound(t);

        if (it == s[i].begin())
            continue;

        res = max(res, *--it + lazy[i]);
    }

    return res;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    len = 1000;  // 1e5的数据下1000貌似更快

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        id[i] = (i - 1) / len + 1;
        s[id[i]].insert(a[i]);
    }

    for (int i = 0; i < n; i++) {
        cin >> opt >> l >> r >> c;

        if (opt == 0)
            add(l, r, c);
        else
            cout << query(l, r, c) << endl;
    }

    return 0;
}