#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define int ll
#define endl "\n"
constexpr int N = 1e5 + 10;
int id[N], a[N], Mul[N], Add[N], n, len;
int mod = 10007;
// 清除标记
void reset(int x) {
    for (int i = (x - 1) * len + 1; i <= min(x * len, n); i++)
        a[i] = (a[i] * Mul[x] + Add[x]) % mod;
    Add[x] = 0;
    Mul[x] = 1;
}

// 0:区间加 1:区间乘
void add(int f, int l, int r, int x) {
    int sid = id[l], eid = id[r];
    reset(sid);
    // 非整块直接操作
    for (int i = l; i <= min(sid * len, r); i++) {
        if (f == 0) a[i] += x;
        else a[i] *= x;
        a[i] %= mod;
    }
    if (sid != eid) {
        reset(eid);
        for (int i = (eid - 1) * len + 1; i <= r; i++) {
            if (f == 0) a[i] += x;
            else a[i] *= x;
            a[i] %= mod;
        }
    }

    for (int i = sid + 1; i < eid; i++) {
        if (f == 0)
            Add[i] = (Add[i] + x) % mod;
        else {
            // * m1 + a1  * m2  - > m1 * m2 + a1 * m2
            Add[i] = (Add[i] * x) % mod;
            Mul[i] = (Mul[i] * x) % mod;
        }
    }
}



signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int op, l, r, x;
    cin >> n;
    len = sqrt(n);

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        id[i] = (i - 1) / len + 1;
    }

    for (int i = 1; i <= id[n]; i++)
        Mul[i] = 1;

    for (int i = 1; i <= n; i++) {
        cin >> op >> l >> r >> x;

        if (op == 2)
            cout << (a[r] * Mul[id[r]] + Add[id[r]]) % mod << endl;
        else
            add(op, l, r, x);
    }

    return 0;
}