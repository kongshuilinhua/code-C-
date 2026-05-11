#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define int ll
#define endl "\n"
constexpr int N = 1e5 + 10;
int id[N], a[N], lazy[N], n, len;
// 把块内改成上次修改的数字
void reset(int x) {
    if (lazy[x] == -1) return;
    for(int i = (x - 1) * len + 1; i <= len * x; i++) a[i] = lazy[x];
    lazy[x] = -1;
}

int add(int l, int r, int x) {
    int sid = id[l], eid = id[r];
    reset(sid);
    int res = 0;
    // 非整块直接操作
    for (int i = l; i <= min(sid * len, r); i++) {
        if (a[i] != x) a[i] = x;
        else res += 1;
    }

    if (sid != eid) {
        reset(eid);
        for (int i = (eid - 1) * len + 1; i <= r; i++) {
            if (a[i] != x) a[i] = x;
            else res += 1;
        }
    }
    for (int i = sid + 1; i < eid; i++) {
        // 有未能set的标记
        if (lazy[i] != -1){
            if (lazy[i] != x) lazy[i] = x;  // 不是x修改成x
            else res += len;                // 是x，加上块内的数字个数
        }else {
            // 无标记，暴力修改。每次最多破坏首尾两个块的标记
            for(int j = (i - 1) * len + 1; j <= i * len; j++){
                if (a[j] != x) a[j] = x;
                else res += 1;
            }
            lazy[i] = x;
        }
    }
    return res;
}



signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int l, r, x;
    cin >> n;
    len = sqrt(n);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        id[i] = (i - 1) / len + 1;
    }
    memset(lazy, -1, sizeof(lazy));
    for (int i = 1; i <= n; i++) {
        cin >> l >> r >> x;
        cout << add(l, r, x) << endl;
    }

    return 0;
}