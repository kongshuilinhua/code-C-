#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define int ll
#define endl "\n"
constexpr int N = 5e4 + 10;
int id[N], a[N], lazy[N], sum[N], len;

void solve_sqrt(int x){
    // 块内部全部为1了,无需开方
    if (lazy[x]) return;
    lazy[x] = 1;
    sum[x] = 0;
    for(int i = (x - 1) *len + 1; i <= x * len; i++){
        a[i] = sqrt(a[i]);
        sum[x] += a[i];
        // 块内部还有元素大于1，可以继续开放。标记为0
        if (a[i] > 1) lazy[x] = 0;
    }
}

void add(int l, int r, int x){
    int sid = id[l], eid = id[r];
    for(int i = l; i <= min(sid * len, r); i++){
        sum[sid] -= a[i];
        a[i] = sqrt(a[i]);
        sum[sid] += a[i];
    }
    if(sid != eid){
      for(int i = (eid - 1) * len +1; i <= r; i++){
        sum[eid] -= a[i];
        a[i] = sqrt(a[i]);
        sum[eid] += a[i];
      }
    }
    // 在同一个块内，直接修改
    for(int i = sid + 1; i < eid; i++)solve_sqrt(i);
}

int query(int l, int r, int p){
    int sid = id[l], eid = id[r];
    int res = 0;
    for(int i = l; i <= min(sid * len, r); i++) res += a[i];
    if (sid != eid){
        for(int i = (eid - 1) * len + 1; i <= r; i++) res += a[i];
    }
    for(int i = sid + 1; i < eid; i++) res += sum[i];
    return res;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, op, l, r, x;
    cin >> n;
    len = sqrt(n);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        id[i] = (i - 1) / len + 1;
        sum[id[i]] += a[i];
    }
    for(int i = 0; i < n; i++){
        cin >> op >> l >> r >> x;
        if (op == 0) add(l, r, x);
        else cout << query(l, r, x + 1) << endl;
    }
    return 0;
}
